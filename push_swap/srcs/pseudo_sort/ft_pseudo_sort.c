/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 15:38:10 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_do_pseudo_sort(t_list ***checks, t_stack *s,
	int pos, int first_pos);
static t_ps	*ft_set_result(t_ps *best, int size, int pos, int first_pos);
static t_ps	*ft_init_result(int size, int pos, int first_pos);

void	ft_pseudo_sort(t_stack *s)
{
	int			i;
	t_ps		*best;
	t_ps		*new;
	t_list		***checks;
	int			score_threshold;

	score_threshold = s->size * SCORE_THRESHOLD;
	checks = ft_init_checks(s->size);
	while (!ft_all_sorted_set(s))
	{
		i = 0;
		best = 0;
		s->lis_lvl++;
		while (i < s->size)
		{
			if (best && best->score > score_threshold)
				break;
			if (!s->stack[i].lis_lvl)
			{
				new = ft_do_pseudo_sort(checks, s, i, i);
				ft_save_check(checks[i], new);
				DEBUG_CODE(
					printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
					printf("    i: %4d\n", i);
				)
				DEBUG_CODE(ft_print_pseudo_sorted(new);)
				ft_take_best(&best, &new);
			}
			i++;
		}
		if (best)
		{
			DEBUG_CODE(
				if (best)
					ft_print_pseudo_sorted(best);
			)
			ft_set_is_sorted(s, best);
			ft_remove_invalid_checks(checks, s);
		}
	}
	DEBUG_CODE(
		printf("STACK A\n");
		ft_print_stack(s);
	)
	DEBUG_CODE(ft_print_checks_nb(checks, s->size);)
	ft_free_checks(checks, s->size);
}

static t_ps	*ft_do_pseudo_sort(t_list ***checks, t_stack *s,
	int pos, int first_pos)
{
	t_ps_rec	rec;
	t_nb		*nb;
	int			i;

	ft_init_ps_rec(&rec, s, pos);
	i = pos + 1;
	while (i < s->size)
	{
		nb = &s->stack[i];
		if (!nb->lis_lvl && nb->nb < rec.pos_nb)
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
	}
	return (ft_set_result(rec.best, s->size, pos, first_pos));
}

static t_ps	*ft_set_result(t_ps *best, int size, int pos, int first_pos)
{
	t_ps	*res;
	
	res = ft_init_result(size, pos, first_pos);
	if (!best)
		return (res);
	pos = (pos + 1) % size;
	while (pos != best->start_pos)
		pos = (pos + 1) % size;
	while (pos != first_pos)
	{
		if (best->hash[pos] != 0)
			res->hash[pos] = 1;
		pos = (pos + 1) % size;
	}
	res->score += best->score;
	best->protection_lvl--;
	return (res);
}

static t_ps	*ft_init_result(int size, int pos, int first_pos)
{
	t_ps	*res;

	res = ft_calloc(1, sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(char));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[pos] = 1;
	res->start_pos = pos;
	res->score = 1;
	res->size = size;
	res->chunk_size = ft_chunk_size(size, pos, first_pos);
	return (res);
}
