/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circling_pseudo_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 19:16:50 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_circling_do_pseudo_sort(t_list ***checks,
	t_stack *s, int pos, int first_pos);
	
void	ft_circling_pseudo_sort(t_stack *s)
{
	int			i;
	t_ps		*best;
	t_ps		*new;
	t_list		***checks;

	i = 0;
	best = 0;
	s->lis_lvl++;
	checks = ft_init_checks(s->size);
	while (i < s->size)
	{
		new = ft_circling_do_pseudo_sort(checks, s, i, i);
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
	ft_free_checks(checks, s->size);
}

static t_ps	*ft_circling_do_pseudo_sort(t_list ***checks,
	t_stack *s, int pos, int first_pos)
{
	t_ps_rec	rec;
	t_nb		*nb;
	int			i;

	ft_init_ps_rec(&rec, s, pos);
	i = (pos + 1) % s->size;
	while (i != first_pos)
	{
		nb = &s->stack[i];
		if (!nb->lis_lvl && nb->nb < rec.pos_nb)
		{
			if (rec.best
				&& rec.best->score > ft_chunk_size(s->size, i, first_pos))
				break;
			rec.new = ft_best_checked(checks[i], s->size, i, first_pos);
			if (!rec.new)
			{
				rec.new = ft_circling_do_pseudo_sort(checks, s, i, first_pos);
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
