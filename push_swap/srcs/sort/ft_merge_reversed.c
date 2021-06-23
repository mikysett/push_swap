/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_reversed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:25:59 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int		ft_get_smallest_nb(t_stack *s);

void	ft_merge_reversed(t_data *data, t_merge_info *m)
{
	DEBUG_CODE(printf("MERGING REVERSED LEVEL: %d\n", m->lvl_from);)
	while (m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from)
	{
		if (m->s_from->stack[m->s_from->top].nb > m->s_in->stack[m->s_in->top].nb
			|| m->s_in->stack[m->s_in->top].lis_lvl != m->lvl_in)
		{
			m->s_from->stack[m->s_from->top].lis_lvl = m->lvl_in;
			ft_push_stack(data, m->in_name);
		}
		else if (ft_only_one_lvl(m->s_in)
			&& m->s_from->stack[m->s_from->top].nb < ft_get_smallest_nb(m->s_in))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->in_name);
	}
	ft_align_s_in(data, m);
}

int		ft_get_smallest_nb(t_stack *s)
{
	int	smallest_nb;
	int	i;

	if (!s->size)
		return (0);
	smallest_nb = s->stack[0].nb;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb < smallest_nb)
			smallest_nb = s->stack[i].nb;
		i++;
	}
	return (smallest_nb);
}
