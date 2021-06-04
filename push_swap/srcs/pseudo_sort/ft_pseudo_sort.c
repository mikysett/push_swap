/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 01:27:04 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_set_result(t_ps *best, int size, int pos, int initial_pos)
{
	t_ps	*res;

	res = malloc(sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(char));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[pos] = 1;
	res->score = 1;
	res->partial_score = 1;
	res->size = size;
	if (pos > initial_pos)
		res->chunk_size = size - pos;
	else
		res->chunk_size = initial_pos - pos;
	if (!best)
		return (res);
	pos++;
	if (pos == size)
		pos = 0;
	while (pos != initial_pos)
	{
		if (best->hash[pos] != 0)
			res->hash[pos] = 1;
		pos++;
		if (pos == size)
			pos = 0;
	}
	res->partial_score += best->partial_score;
	res->score += best->partial_score;


	// int i;
	// i = 0;
	// printf(CLR_YELLOW);
	// while (i < size)
	// {
	// 	printf("%d", res->hash[i]);
	// 	i++;
	// }
	// printf("\n");
	// printf(CLR_WHITE);
	
	return (res);
}

static bool	ft_is_nb_eligible(t_nb *nb, int rec_pos_nb)
{
	if (!nb->is_sorted && nb->nb < rec_pos_nb)
		return (true);
	return (false);
}

static t_ps	*ft_do_pseudo_sort(t_list ***checks, t_stack *s, int pos, int initial_pos)
{
	t_ps_rec	rec;
	t_nb		*nb;
	int			i;

	ft_init_ps_rec(&rec, s, pos);
	i = (pos + 1) % s->size;
	while (i != initial_pos)
	{
		nb = &s->stack[i];
		if (!nb->is_sorted && nb->nb < rec.pos_nb)
		{
			// Recursion depth limit
			// if (ps_data->nb_rec > MAX_REC)
			// 	break;
			rec.new = ft_best_checked(checks[i], s->size, i, initial_pos);
			if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(checks, s, i, initial_pos);
				// DEBUG_CODE(printf("%sRECAL: nb_rec: %ld%s - ", CLR_YELLOW, ps_data->nb_rec, CLR_WHITE);)
				
				ft_save_check(checks[i], rec.new);
				
				// ft_print_checks(ps_data->checks, s->size);

				// ps_data->nb_rec++;
			}
			ft_take_partial_best(&rec.best, &rec.new);
			// NO recursion depth limit
			// if (rec.best->score > s->size - pos)
			// 	break;
		}
		i++;
		if (i == s->size)
			i = 0;
	}
	// if (pos == 0)
	// 	ft_exit_failure();
	// printf("s->size(%d) + pos(%d): %d\n\n", s->size, pos, s->size + pos);
	return (ft_set_result(rec.best, s->size, pos, initial_pos));
}

void	ft_pseudo_sort(t_stack *s)
{
	int			i;
	t_ps		*best;
	t_ps		*new;
	t_list		***checks;

	i = 0;
	best = 0;
	s->sorting_level++;

	// ft_init_ps_data(&ps_data, s);
	checks = ft_init_checks(s->size);
	while (i < s->size)
	{
		// i_nb = s->stack[i].nb;
		// ps_data.new = ft_abs_best_checked(ps_data.checks[i]);
		// if (!ps_data.new)
		{
			new = ft_do_pseudo_sort(checks, s, i, i);
			ft_save_check(checks[i], new);
			
			// ft_print_pseudo_sorted(ps_data.new);
		}
		DEBUG_CODE(
			printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
			printf("    i: %4d\n", i);
		)
		// To switch recursions from global nb to single rec execution number
		// ps_data.nb_rec = 0;
		DEBUG_CODE(ft_print_pseudo_sorted(new);)
		ft_take_best(&best, &new);
		// if (ps_data.best->score >= s->size - i)
		// 	break;
		i++;
	}
	DEBUG_CODE(ft_print_pseudo_sorted(best);)

	ft_set_is_sorted(s, best);
	s->nb_sorted = best->score;
	DEBUG_CODE(printf("nb_sorted: %d\n", best->score);)

	ft_free_checks(checks, s->size);
}
