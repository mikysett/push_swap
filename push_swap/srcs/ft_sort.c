/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 14:40:46 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	prev_p(int pos, int step, int stack_size)
{
	if (pos - step < 0)
		return (stack_size + (pos - step));
	else
		return (pos - step);
}

int	next_p(int pos, int step, int stack_size)
{
	if (pos + step > stack_size - 1)
		return (pos + step - stack_size);
	else
		return (pos + step);
}

static void	ft_rotate_sorted(t_data *data)
{
	int	curr_pos;

	curr_pos = -1;
	while (++curr_pos < data->s_a.size)
		if (data->s_a.stack[curr_pos].sort_pos == 0)
			break;
	if (curr_pos <= data->s_a.size / 2)
		while (curr_pos-- != 0)
			ft_reverse_rotate_a(data);
	else
	{
		curr_pos = data->s_a.size - curr_pos;
		while (curr_pos-- != 0)
			ft_rotate_a(data);
	}
}

static void	ft_set_edge_sort_pos(t_stack *s)
{
	int	i;

	i = -1;
	s->smaller_sort_pos = s->size;
	s->bigger_sort_pos = -1;
	while (++i < s->size)
	{
		if (!s->stack[i].is_sorted)
			continue;
		if (s->smaller_sort_pos > s->stack[i].sort_pos)
			s->smaller_sort_pos = s->stack[i].sort_pos;
		if (s->bigger_sort_pos < s->stack[i].sort_pos)
			s->bigger_sort_pos = s->stack[i].sort_pos;
	}
}

bool	ft_sort(t_data *data)
{
	ft_set_pos(&data->s_a, true);
	ft_set_sort_pos(&data->s_a, 0, data->s_a.size - 1);
	if (ft_duplicated_nb(&data->s_a))
		return (false);
	DEBUG_CODE(ft_is_sorted(&data->s_a);)
	ft_fix_pos(&data->s_a);
	ft_pseudo_sort(&data->s_a);
	// To test
	DEBUG_CODE(
		printf("PSEUDO SORTING CHECKS COMPLETED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
	)
	// while (1)
	// {
	// 	;
	// }
	data->wait_to_swap = true;
	data->s_b.has_in_range = false;
	ft_set_edge_sort_pos(&data->s_a);
	ft_generate_ops(data);
	ft_rotate_sorted(data);
	ft_print_ops(data, op_none);
	return (true);
}
