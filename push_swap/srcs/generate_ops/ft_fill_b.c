/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 14:55:26 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_is_rotate_better(t_data *data)
{
	int	i;
	int	op_by_rotate;
	int	op_by_reverse;

	op_by_rotate = 0;
	i = 0;
	while (data->s_a.stack[i].is_sorted)
		i++;
	op_by_reverse = i + 1;
	i = data->s_a.size - 1;
	while (i != op_by_reverse - 1)
	{
		if (data->s_a.stack[i].is_sorted)
			op_by_rotate++;
		else
			op_by_rotate = 0;
		i--;
	}
	if (op_by_rotate < op_by_reverse)
	{
		DEBUG_CODE(printf("by rotate\n");)
		return (true);
	}
	DEBUG_CODE(printf("BY REVERSE ROTATE\n");)
	return (false);
}

static bool	ft_optimal_swap(t_data *data, t_stack *a, t_stack *b)
{
	int	a_top;
	int	b_top;

	a_top = a->size - 1;
	b_top = b->size - 1;
	if (a_top > 0 && b_top > 0
		&& a->stack[a_top - 1].is_sorted == false
		&& b->stack[b_top].nb < b->stack[b_top - 1].nb
		&& a->stack[a_top].nb > a->stack[a_top - 1].nb
		&& b->stack[b_top].in_range == b->stack[b_top - 1].in_range)
		ft_swap_2(data);
	else
		return (false);
	return (true);
}

static void	ft_optimal_reverse_push(t_data *data)
{
	t_nb	*first;
	t_nb	*last;

	last = &data->s_a.stack[data->s_a.size - 1];
	first = &data->s_a.stack[0];
	while (first->is_sorted != 1)
	{
		if (!first->is_sorted && !last->is_sorted && last > first)
		{
			DEBUG_CODE(printf("orp - ");)
			ft_push_b(data);
		}
		else
		{
			ft_reverse_rotate_a(data);
			last = &data->s_a.stack[data->s_a.size - 1];
		}
		first = &data->s_a.stack[0];
	}
}

static bool	ft_possible_sort_by_top(t_stack *s, int nb_sort_pos,
	int start, bool recursive)
{
	if (start < 0)
		return (false);
	if (s->stack[start].is_sorted == 1)
	{
		if (s->stack[start].sort_pos == s->smaller_sort_pos
			&& (nb_sort_pos > s->bigger_sort_pos || nb_sort_pos < s->smaller_sort_pos))
			return (true);
		else if (recursive)
			return (ft_possible_sort_by_top(s, s->stack[start].sort_pos,
					start - 1, true));
		else
			return (false);
	}
	else if (recursive)
		return (ft_possible_sort_by_top(s, s->stack[start].sort_pos,
				start - 1, true));
	else
		return (false);
}

static void	ft_update_edge_sort_pos(t_stack *s, int nb_sort_pos)
{
		if (nb_sort_pos > s->bigger_sort_pos)
			s->bigger_sort_pos = nb_sort_pos;
		else
			s->smaller_sort_pos = nb_sort_pos;
}

void	ft_update_b(t_data *data, t_stack *s)
{
	int	top;

	if (!s->size)
		return ;
	top = s->size - 1;
	if (!s->has_in_range && s->stack[top].in_range == true)
		s->has_in_range = true;
	if (s->has_in_range && s->stack[top].in_range == false)
		ft_rotate_b(data);
}

void	ft_fill_b(t_data *data)
{
	int	prev_sorted_i;
	int	next_sorted_i;
	int	top;

	top = data->s_a.size - 1;
	while (data->s_a.stack[top].is_sorted != 1)
	{
		if (ft_possible_sort_by_top(&data->s_a,
				data->s_a.stack[top].sort_pos,
				top - 1, false))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[top].is_sorted = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.stack[top].sort_pos);
			ft_swap_a(data);
			break;
		}
		prev_sorted_i = prev_sorted(&data->s_a, top - 2);
		next_sorted_i = next_sorted(&data->s_a, 1);
		if (data->s_a.stack[top - 1].is_sorted == 1
				&& ft_is_sort_pos(&data->s_a,
					top - 1 - prev_sorted_i,
					data->s_a.stack[top].sort_pos,
					prev_sorted_i))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[top].is_sorted = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.stack[top].sort_pos);
			ft_swap_a(data);
			break;
		}
		else if (data->s_a.stack[0].is_sorted == 1
				&& ft_is_sort_pos(&data->s_a,
					next_sorted_i,
					data->s_a.stack[top].sort_pos,
					0))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[top].is_sorted = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.stack[top].sort_pos);
			ft_reverse_rotate_a(data);
			ft_swap_a(data);
		}
		else
		{
			top--;
			ft_push_b(data);
			ft_update_b(data, &data->s_b);
			if (data->wait_to_swap == true)
				data->wait_to_swap = false;
			else if (ft_optimal_swap(data, &data->s_a, &data->s_b))
				data->wait_to_swap = true;
		}
	}
}
