/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/03 08:24:34 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_set_result(t_ps *best, bool circled, int first_nb, int size)
{
	int		i;
	int		j;
	t_ps	*res;

	res = malloc(sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(bool));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[0] = true;
	res->score = 1;
	res->size = size;
	res->circled = circled;
	res->lower_nb = first_nb;
	if (!best)
		return (res);
	res->circled = best->circled;
	i = size - 1;
	j = best->size - 1;
	while (j >= 0)
		res->hash[i--] = best->hash[j--];
	res->score += best->score;
	return (res);
}

static bool	ft_is_nb_eligible(t_nb *nb, int rec_pos_nb, bool circled,
	int first_nb)
{
	if (!nb->is_sorted && 
		((nb->nb < rec_pos_nb && (circled == false
			|| (circled == true && nb->nb > first_nb)))
				|| (circled == false && nb->nb > first_nb)))
		return (true);
	return (false);
}

static t_ps	*ft_do_pseudo_sort(t_ps_data *ps_data, bool circled, int pos,
	int first_nb)
{
	t_ps_rec	rec;
	int			i;

	ft_init_ps_rec(&rec, ps_data->s, pos);
	ps_data->nb_rec++;
	i = pos;
	while (++i < rec.s_size)
		if (ft_is_nb_eligible(&ps_data->s->stack[i],
				rec.pos_nb, circled, first_nb))
		{
			// Recursion depth limit
			if (ps_data->nb_rec > MAX_REC)
				break;
			if (ps_data->s->stack[i].nb > rec.pos_nb)
			{
				rec.new = ft_best_checked(ps_data->checks[i], true, first_nb);
				if (rec.new)
					rec.new->circled = true;
			}
			else
				rec.new = ft_best_checked(ps_data->checks[i], circled, first_nb);
			if (!rec.new)
			{
				if (ps_data->s->stack[i].nb > rec.pos_nb)
				{
					rec.new = ft_do_pseudo_sort(ps_data, true, i, first_nb);
					rec.new->circled = true;
				}
				else
					rec.new = ft_do_pseudo_sort(ps_data, circled, i, first_nb);
				// DEBUG_CODE(printf("%sRECAL: nb_rec: %ld%s - ", CLR_YELLOW, ps_data->nb_rec, CLR_WHITE);)
				ft_save_check(ps_data->checks[i], rec.new);
			}
			ft_take_best(&rec.best, &rec.new);
			// NO recursion depth limit
			if (rec.best->score > rec.s_size - pos)
				break;
		}
	return (ft_set_result(rec.best, circled, first_nb, rec.s_size - pos));
}

void	ft_pseudo_sort(t_stack *s)
{
	int			i;
	int			i_nb;
	bool		circled_v;
	bool		linear_v;

	t_ps_data	ps_data;

	i = 0;
	s->sorting_level++;
	ft_init_ps_data(&ps_data, s);

	while (i < s->size - 1)
	{
		i_nb = s->stack[i].nb;
		ps_data.new = ft_abs_best_checked(ps_data.checks[i], &linear_v, &circled_v);
		if (!ps_data.new || !linear_v || !circled_v)
		{
			ps_data.new = ft_do_pseudo_sort(&ps_data, false, i, i_nb);
			ft_save_check(*ps_data.checks, ps_data.new);
		}
		DEBUG_CODE(
			printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
			if (ps_data.nb_rec > 0)
				printf("i: %10d, nb_rec: %ld\n", i, ps_data.nb_rec);
		)
		// To switch recursions from global nb to single rec execution number
		// ps_data.nb_rec = 0;
		DEBUG_CODE(ft_print_pseudo_sorted(ps_data.new);)
		ft_take_best(&ps_data.best, &ps_data.new);
		if (ps_data.best->score >= s->size - i)
			break;
		i++;
	}
	DEBUG_CODE(ft_print_pseudo_sorted(ps_data.best);)

	// Good one
	ft_set_is_sorted(s, ps_data.best);
	s->nb_sorted = ps_data.best->score;

	// Test one
	// if (ps_data.best->score == 3 && s->size >= 5
	// 	&& s->stack[4].is_sorted == 1
	// 	&& s->stack[3].is_sorted == 1)
	// {
	// 	s->stack[0].is_sorted = 1;
	// 	s->stack[1].is_sorted = 1;
	// 	s->stack[2].is_sorted = false;
	// 	s->stack[3].is_sorted = false;
	// 	s->stack[4].is_sorted = false;
	// 	s->nb_sorted = 2;
	// }

	ft_free_checks(&ps_data);
}
