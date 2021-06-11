/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/08 21:45:46 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_set_result(t_ps *best, int size, int pos, int first_pos)
{
	t_ps	*res;
	bool	is_aligned;
	
	res = malloc(sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(char));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[pos] = 1;
	res->start_pos = pos;
	res->score = 1;
	res->size = size;
	res->protection_lvl = 0;
	res->chunk_size = ft_chunk_size(size, pos, first_pos);
	if (!best)
		return (res);
	// printf("res->chunk size: %d, best->chunk size: %d\n",
	// 	res->chunk_size, best->chunk_size);
	pos = (pos + 1) % size;
	is_aligned = false;
	while (pos != first_pos)
	{
		if (pos == best->start_pos)
			is_aligned = true;
		if (is_aligned && best->hash[pos] != 0)
			res->hash[pos] = 1;
		pos++;
		if (pos == size)
			pos = 0;
	}
	res->score += best->score;
	best->protection_lvl--;
	return (res);
}

static t_ps	*ft_do_pseudo_sort(t_list ***checks, t_stack *s, int pos, int first_pos)
{
	t_ps_rec	rec;
	t_nb		*nb;
	int			i;

	ft_init_ps_rec(&rec, s, pos);
	i = (pos + 1) % s->size;
	while (i != first_pos)
	{
		nb = &s->stack[i];
		if (!nb->is_sorted && nb->nb < rec.pos_nb)
		{
			// Recursion depth limit
			// if (ps_data->nb_rec > MAX_REC)
			// 	break;
			if (rec.best
				&& rec.best->score >= ft_chunk_size(s->size, i, first_pos))
				break;
			rec.new = ft_best_checked(checks[i], s->size, i, first_pos);
			if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(checks, s, i, first_pos);
				ft_save_check(checks[i], rec.new);
			}
			ft_take_best(&rec.best, &rec.new);
		}
		i++;
		if (i == s->size)
			i = 0;
	}
	return (ft_set_result(rec.best, s->size, pos, first_pos));
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
	checks = ft_init_checks(s->size);
	while (i < s->size)
	{
		if (best
			&& best->score > s->size * 0.90)
			break;
		new = ft_do_pseudo_sort(checks, s, i, i);
		ft_save_check(checks[i], new);
		DEBUG_CODE(
			printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
			printf("    i: %4d\n", i);
		)
		DEBUG_CODE(ft_print_pseudo_sorted(new);)
		ft_take_best(&best, &new);
		i++;
	}
	DEBUG_CODE(ft_print_pseudo_sorted(best);)

	ft_set_is_sorted(s, best);
	s->nb_sorted = best->score;
	DEBUG_CODE(printf("nb_sorted: %d\n", best->score);)
	// ft_print_checks(checks, s->size);
	DEBUG_CODE(ft_print_checks_nb(checks, s->size);)
	ft_free_checks(checks, s->size);
}
