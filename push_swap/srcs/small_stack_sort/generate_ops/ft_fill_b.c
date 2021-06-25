/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 02:09:27 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"


void	ft_fill_b(t_data *data)
{
	int	prev_sorted_i;
	int	next_sorted_i;
	
	data->s_a.nb_sorted = ft_get_lvl_size(&data->s_a, 1);
	while (data->s_a.size &&
		data->s_a.stack[data->s_a.top].lis_lvl != 1)
	{
		if (ft_possible_sort_by_top(&data->s_a,
				data->s_a.stack[data->s_a.top].sort_pos,
				data->s_a.size - 2, false))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[data->s_a.top].lis_lvl = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.top);
			ft_swap_a(data);
			ft_fill_b(data);
			return ;
		}

		prev_sorted_i = prev_sorted(&data->s_a, data->s_a.size - 3);
		next_sorted_i = next_sorted(&data->s_a, 1);
		if (data->s_a.stack[data->s_a.size - 2].lis_lvl == 1
				&& ft_is_sort_pos(&data->s_a,
					data->s_a.size - 2 - prev_sorted_i,
					data->s_a.stack[data->s_a.top].sort_pos,
					prev_sorted_i))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[data->s_a.top].lis_lvl = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.top);
			ft_swap_a(data);
			ft_fill_b(data);
			return ;
		}
		else if (
			!(ft_possible_sort_by_top(&data->s_a,
				data->s_a.stack[data->s_a.size - 2].sort_pos,
				data->s_a.size - 3, true))
			&&
			data->s_a.stack[0].lis_lvl == 1
				&& ft_is_sort_pos(&data->s_a,
					next_sorted_i,
					data->s_a.stack[data->s_a.top].sort_pos,
					0))
		{
			data->s_a.nb_sorted++;
			data->s_a.stack[data->s_a.top].lis_lvl = 1;
			ft_update_edge_sort_pos(&data->s_a, data->s_a.top);
			ft_reverse_rotate_a(data);
			ft_swap_a(data);
			ft_fill_b(data);
			return ;
		}
		ft_push_b(data);
		if (data->wait_to_swap == true)
			data->wait_to_swap = false;
		else if (ft_optimal_swap(data))
			data->wait_to_swap = true;
	}
	if (!data->s_a.size || data->s_a.nb_sorted == data->s_a.size)
		return ;
	if (ft_is_rotate_better(data))
		while (data->s_a.stack[data->s_a.top].lis_lvl == 1)
			ft_rotate_a(data);
	else
	{
		while (data->s_a.stack[0].lis_lvl == 1)
			ft_reverse_rotate_a(data);
		ft_optimal_reverse_push(data);
	}
	ft_fill_b(data);
}

void	ft_update_edge_sort_pos(t_stack *s, int nb_index)
{
	if (s->stack[nb_index].sort_pos > s->bigger_sp)
		s->bigger_sp = s->stack[nb_index].sort_pos;
	else if (s->stack[nb_index].sort_pos < s->smaller_sp)
		s->smaller_sp = s->stack[nb_index].sort_pos;
}

bool	ft_is_rotate_better(t_data *data)
{
	int	i;
	int	op_by_rotate;
	int	op_by_reverse;

	op_by_rotate = 0;
	i = 0;
	while (data->s_a.stack[i].lis_lvl)
		i++;
	op_by_reverse = i + 1;
	i = data->s_a.top;
	while (i != op_by_reverse - 1)
	{
		if (data->s_a.stack[i].lis_lvl)
			op_by_rotate++;
		else
			op_by_rotate = 0;
		i--;
	}
	if (op_by_rotate < op_by_reverse)
		return (true);
	return (false);
}

bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos)
{
	int	next_p_i;

	next_p_i = next_p(pos, step, s->size);
	if ((nb_sort_pos > s->stack[pos].sort_pos
		&& nb_sort_pos < s->stack[next_p_i].sort_pos)
		|| (nb_sort_pos > s->bigger_sp
			&& s->stack[pos].sort_pos == s->bigger_sp)
		|| (nb_sort_pos < s->smaller_sp
			&& s->stack[next_p_i].sort_pos == s->smaller_sp))
		return (true);
	return (false);
}

bool	ft_possible_sort_by_top(t_stack *s, int nb_sort_pos,
	int start, bool recursive)
{
	if (start < 0)
		return (false);
	if (s->stack[start].lis_lvl == 1)
	{
		if (s->stack[start].sort_pos == s->smaller_sp
			&& (nb_sort_pos > s->bigger_sp || nb_sort_pos < s->smaller_sp))
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
