/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 17:53:31 by msessa           ###   ########.fr       */
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
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_reverse_rotate_a(data);
		}
	else
	{
		curr_pos = data->s_a.size - curr_pos;
		while (curr_pos-- != 0)
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_rotate_a(data);
		}
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

void	ft_sort(t_data *data)
{

	// To test
	// while (1)
	// {
	// 	;
	// }
	ft_set_edge_sort_pos(&data->s_a);

	ft_extract_ranges(data);
	
	// TODO
	// ft_organize_not_in_range(data);
	
	ft_generate_ops(data);


	ft_rotate_sorted(data);
	ft_print_ops(data, op_none);
}
