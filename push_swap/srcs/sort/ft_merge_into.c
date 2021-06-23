/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_into.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:41:50 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_it_is_mergable(t_data *data, t_merge_info *m);
static int	ft_get_biggest_nb(t_stack *s);

void	ft_merge_into(t_data *data, t_merge_info *m)
{
	DEBUG_CODE(printf("MERGING LEVEL: %d\n", m->lvl_from);)
	while (ft_it_is_mergable(data, m))
	{
		if (m->s_from->top >= 0
			&& m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from
			&& (m->s_from->stack[m->s_from->top].nb < m->s_in->stack[m->s_in->top].nb
			|| m->s_in->stack[m->s_in->top].lis_lvl != m->lvl_in))
		{
			m->s_from->stack[m->s_from->top].lis_lvl = m->lvl_in;
			ft_push_stack(data, m->in_name);
		}
		else if (m->s_from->top >= 0
			&& (ft_only_one_lvl(m->s_in)
			&& m->s_from->stack[m->s_from->top].nb > ft_get_biggest_nb(m->s_in)))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->in_name);
		// ft_print_stack_ligh(data);
	}
	ft_align_s_in(data, m);
}

static bool	ft_it_is_mergable(t_data *data, t_merge_info *m)
{
	while (ft_count_lvl(m->s_from) > 1 && ft_merge_from_bottom(data, m))
		continue;
	return ((m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from)
		|| (ft_count_lvl(m->s_in) != 1
			&& m->s_in->stack[m->s_in->top].lis_lvl == m->lvl_in));
}

void	ft_merge_tail(t_data *data, t_merge_info *m,
	int lvl_to_sort, int dest_lvl)
{
	ft_rotate_sorted(data, m->in_name);
	while (m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == lvl_to_sort)
	{
		m->s_from->stack[m->s_from->top].lis_lvl = dest_lvl;
		ft_push_stack(data, m->in_name);
		ft_rotate_stack(data, m->in_name);
	}
}

static int		ft_get_biggest_nb(t_stack *s)
{
	int	biggest_nb;
	int	i;

	if (!s->size)
		return (0);
	biggest_nb = s->stack[0].nb;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb > biggest_nb)
			biggest_nb = s->stack[i].nb;
		i++;
	}
	return (biggest_nb);
}
