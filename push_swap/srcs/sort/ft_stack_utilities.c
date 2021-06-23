/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:40:36 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_s_name	ft_opposite_s(t_s_name current_stack)
{
	if (current_stack == stack_a)
		return (stack_b);
	return (stack_a);
}

void	ft_init_stacks_name(t_data *data, t_merge_info *m)
{
	if (m->in_name == stack_a)
	{
		m->s_in = &data->s_a;
		m->s_from = &data->s_b;
	}
	else
	{
		m->s_in = &data->s_b;
		m->s_from = &data->s_a;
	}
}

void	ft_align_s_in(t_data *data, t_merge_info *m)
{
	if (!ft_only_one_lvl(m->s_in))
		while (m->s_in->stack[m->s_in->top].lis_lvl == m->lvl_in)
			ft_rotate_stack(data, m->in_name);
	else
		ft_rotate_sorted(data, m->in_name);
}
