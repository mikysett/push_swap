/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 01:43:50 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_generate_ops(t_data *data)
{
	data->wait_to_swap = true;
	ft_set_edge_sort_pos(&data->s_a);
	ft_fill_b(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
	ft_sort_in_a(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
}

void	ft_set_edge_sort_pos(t_stack *s)
{
	int	i;

	i = -1;
	s->smaller_sp = s->size;
	s->bigger_sp = -1;
	while (++i < s->size)
	{
		if (!s->stack[i].lis_lvl)
			continue;
		if (s->smaller_sp > s->stack[i].sort_pos)
			s->smaller_sp = s->stack[i].sort_pos;
		if (s->bigger_sp < s->stack[i].sort_pos)
			s->bigger_sp = s->stack[i].sort_pos;
	}
}
