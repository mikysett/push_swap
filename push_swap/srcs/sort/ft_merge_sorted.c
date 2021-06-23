/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 16:00:39 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_merge_sorted(t_data *data)
{
	t_merge_info	merge;

	merge.reverse_into_b = true;
	while (data->s_b.size)
	{
		ft_compact_top(data, &data->s_a, stack_a);
		ft_compact_top(data, &data->s_b, stack_b);
		ft_init_merge(data, &merge);
		if (merge.reversed_merge)
			ft_merge_reversed(data, &merge);
		else
			ft_merge_into(data, &merge);
		DEBUG_CODE(
			ft_print_stack_ligh(data);
			ft_print_ops(data, op_none);
		)
		if (!data->s_b.size && ft_count_lvl(&data->s_a) > 1)
			ft_swap_lvl(data, stack_b, &data->s_a);
		else if (!data->s_a.size)
		{
			if (ft_top_lvl_reversed(&data->s_b, data->s_b.top))
				ft_swap_lvl(data, stack_a, &data->s_b);
			else
				ft_reverse_swap_lvl(data, stack_a, &data->s_b);
		}
	}
}

void	ft_compact_top(t_data *data, t_stack *s, t_s_name s_name)
{
	if (s->top > 1
		&& s->stack[s->top].lis_lvl != s->stack[s->top - 1].lis_lvl
		&& !ft_top_lvl_reversed(s, s->top - 1)
		&& (s->top < 2
			|| s->stack[s->top - 2].lis_lvl != s->stack[s->top - 1].lis_lvl
			|| ft_can_be_in_middle(s->stack[s->top].nb,
				&s->stack[s->top - 1], &s->stack[s->top - 2])))
	{
		s->stack[s->top].lis_lvl = s->stack[s->top - 1].lis_lvl;
		ft_swap_stack(data, s_name);
	}
}
