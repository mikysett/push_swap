/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_from_bottom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 16:15:10 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_eligible_for_bottom_merge(t_merge_info *m);
static t_nb	*ft_set_prev_for_bottom_merge(t_merge_info *m);
static t_nb	*ft_set_next_for_bottom_merge(t_merge_info *m);

bool	ft_merge_from_bottom(t_data *data, t_merge_info *m)
{
	t_nb	*bottom_nb;
	t_nb	*prev_nb;
	t_nb	*next_nb;

	bottom_nb = &m->s_from->stack[0];
	DEBUG_CODE(printf("Trying to merge nb: %d\n", bottom_nb->nb);)
	if (!ft_eligible_for_bottom_merge(m))
		return (false);
	prev_nb = ft_set_prev_for_bottom_merge(m);
	next_nb = ft_set_next_for_bottom_merge(m);
	DEBUG_CODE(
		printf("bottom_nb: %d\n", bottom_nb->nb);
		if (prev_nb)
			printf("prev_nb: %d\n", prev_nb->nb);
		else
			printf("prev_nb: NULL\n");
		if (next_nb)
			printf("next_nb: %d\n", next_nb->nb);
		else
			printf("next_nb: NULL\n");
	)
	if (ft_can_be_in_middle(bottom_nb->nb, prev_nb, next_nb))
	{
		DEBUG_CODE(
			printf("MERGING FROM BOTTOM!\n");
		)
		m->s_from->stack[0].lis_lvl = m->lvl_in;
		ft_reverse_rotate_stack(data, !m->in_name);
		ft_push_stack(data, m->in_name);
		if (next_nb && prev_nb
			&& prev_nb->nb > next_nb->nb)
			ft_rotate_stack(data, m->in_name);
		return (true);
	}
	return (false);
}

static bool	ft_eligible_for_bottom_merge(t_merge_info *m)
{
	if (ft_count_lvl(m->s_from) == 1
		|| (ft_get_lvl_size(m->s_from, m->s_from->stack[0].lis_lvl) > 1
			&& !ft_bottom_lvl_reversed(m->s_from, 0)))
		return (false);
	return (true);
}

static t_nb	*ft_set_prev_for_bottom_merge(t_merge_info *m)
{
	const t_nb	*s_from_top_nb = &m->s_from->stack[m->s_from->top];
	const t_nb	*s_in_top_nb = &m->s_in->stack[m->s_in->top];

	if (s_from_top_nb->lis_lvl == m->lvl_from
		&& (s_in_top_nb->lis_lvl != m->lvl_in))
		return ((t_nb *)s_from_top_nb);
	else if (m->s_in->stack[0].lis_lvl == m->lvl_in)
		return (&m->s_in->stack[0]);
	else
		return (0);
}
static t_nb	*ft_set_next_for_bottom_merge(t_merge_info *m)
{
	const t_nb	*s_from_top_nb = &m->s_from->stack[m->s_from->top];
	const t_nb	*s_in_top_nb = &m->s_in->stack[m->s_in->top];

	if (s_in_top_nb->lis_lvl == m->lvl_in
		&& (s_from_top_nb->lis_lvl != m->lvl_from
			|| s_from_top_nb->nb > s_in_top_nb->nb))
		return ((t_nb *)s_in_top_nb);
	else if (s_from_top_nb->lis_lvl == m->lvl_from)
		return ((t_nb *)s_from_top_nb);
	else
		return (0);
}