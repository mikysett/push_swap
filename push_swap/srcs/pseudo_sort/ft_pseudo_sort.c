/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/03 18:43:30 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_set_result(t_ps *best, int size, int pos, int initial_pos)
{
	int		i;
	t_ps	*res;

	res = malloc(sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(bool));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[0] = 1;
	res->score = 1;
	res->size = size;
	if (!best)
		return (res);
	i = 0;
	printf("best hash (pos: %d):\n", pos);
	while (i < size)
	{
		printf("%d", best->hash[i]);
		if (best->hash[i] != 0)
			res->hash[(i + pos) % size] = best->hash[i];
		i++;
	}
	printf("\n");
	res->score += best->score;
	return (res);
}

static bool	ft_is_nb_eligible(t_nb *nb, int rec_pos_nb)
{
	if (!nb->is_sorted && nb->nb < rec_pos_nb)
		return (true);
	return (false);
}

static t_ps	*ft_do_pseudo_sort(t_ps_data *ps_data, int pos, int initial_pos)
{
	t_ps_rec	rec;
	int			i;

	ft_init_ps_rec(&rec, ps_data->s, pos);
	i = pos;
	while (++i % ps_data->s->size != initial_pos)
	{
		// if (pos == 0)
		// 	printf("i %% = %d - ", i % ps_data->s->size);
		if (ft_is_nb_eligible(&ps_data->s->stack[i % ps_data->s->size], rec.pos_nb))
		{
			// Recursion depth limit
			// if (ps_data->nb_rec > MAX_REC)
			// 	break;
			// rec.new = ft_best_checked(ps_data->checks[i % ps_data->s->size]);
			// if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(ps_data, i % ps_data->s->size, initial_pos);
				// DEBUG_CODE(printf("%sRECAL: nb_rec: %ld%s - ", CLR_YELLOW, ps_data->nb_rec, CLR_WHITE);)
				ft_save_check(ps_data->checks[i % ps_data->s->size], rec.new);
				// ft_print_checks(ps_data->checks, ps_data->s->size);
				ps_data->nb_rec++;
			}
			ft_take_best(&rec.best, &rec.new);
			// NO recursion depth limit
			// if (rec.best->score > ps_data->s->size - pos)
			// 	break;
		}
	}
	// if (pos == 0)
	// 	ft_exit_failure();
	// printf("ps_data->s->size(%d) + pos(%d): %d\n\n", ps_data->s->size, pos, ps_data->s->size + pos);
	return (ft_set_result(rec.best, ps_data->s->size, pos, initial_pos));
}

void	ft_pseudo_sort(t_stack *s)
{
	int			i;
	int			i_nb;

	t_ps_data	ps_data;

	i = 0;
	s->sorting_level++;
	ft_init_ps_data(&ps_data, s);

	while (i < s->size - 1)
	{
		i_nb = s->stack[i].nb;
		ps_data.new = ft_abs_best_checked(ps_data.checks[i]);
		if (!ps_data.new)
		{
			printf("pos: %d\n\n", i);
			ps_data.new = ft_do_pseudo_sort(&ps_data, i, i);
			ft_save_check(*ps_data.checks, ps_data.new);
			// ft_print_pseudo_sorted(ps_data.new);
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

	ft_set_is_sorted(s, ps_data.best);
	s->nb_sorted = ps_data.best->score;

	ft_free_checks(&ps_data);
}
