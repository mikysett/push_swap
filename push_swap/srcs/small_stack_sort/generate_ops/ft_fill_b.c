/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 13:28:04 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_try_to_sort_top(t_data *data, t_stack *s);
static bool	ft_can_sort_top_nb(t_stack *s);
static bool	ft_can_sort_bottom_nb(t_stack *s);
static void	ft_move_a_to_next_unsorted(t_data *data);

void	ft_fill_b(t_data *data)
{
	data->s_a.nb_sorted = ft_get_lvl_size(&data->s_a, 1);
	while (data->s_a.size > data->s_a.nb_sorted)
	{
		if (data->s_a.stack[data->s_a.top].lis_lvl != 1)
		{
			if (!ft_try_to_sort_top(data, &data->s_a))
			{
				ft_push_b(data);
				if (data->wait_to_swap)
					data->wait_to_swap = false;
				else if (ft_optimal_swap(data))
					data->wait_to_swap = true;
			}
		}
		else
			ft_move_a_to_next_unsorted(data);
	}
}

static bool	ft_try_to_sort_top(t_data *data, t_stack *s)
{
	if (ft_can_sort_top_nb(s))
	{
		s->stack[s->top].lis_lvl = 1;
		ft_update_edge_sort_pos(s, s->top);
		ft_swap_a(data);
	}
	else if (ft_can_sort_bottom_nb(s))
	{
		s->stack[s->top].lis_lvl = 1;
		ft_update_edge_sort_pos(s, s->top);
		ft_reverse_rotate_a(data);
		ft_swap_a(data);
	}
	else
		return (false);
	s->nb_sorted++;
	return (true);
}

static bool	ft_can_sort_top_nb(t_stack *s)
{
	int	prev_sort_i;
	int	next_sort_i;

	prev_sort_i = prev_sorted(s, s->top - 2);
	next_sort_i = next_sorted(s, 1);
	if (ft_possible_sort_by_top(s,
			s->stack[s->top].sort_pos,
			s->top - 1, false)
		|| (prev_sort_i >= 0 && next_sort_i <= s->top
			&& s->stack[s->top - 1].lis_lvl == 1
			&& ft_is_sort_pos(s,
				s->top - 1 - prev_sort_i,
				s->stack[s->top].sort_pos,
				prev_sort_i)))
		return (true);
	return (false);
}

static bool	ft_can_sort_bottom_nb(t_stack *s)
{
	int	next_sort_i;

	next_sort_i = next_sorted(s, 1);
	if (!(ft_possible_sort_by_top(s,
			s->stack[s->top - 1].sort_pos,
			s->top - 2, true))
		&& s->stack[0].lis_lvl == 1
		&& ft_is_sort_pos(s,
			next_sort_i,
			s->stack[s->top].sort_pos,
			0))
		return (true);
	return (false);
}

static void	ft_move_a_to_next_unsorted(t_data *data)
{
	if (ft_is_rotate_better(data))
		while (data->s_a.stack[data->s_a.top].lis_lvl == 1)
			ft_rotate_a(data);
	else
	{
		while (data->s_a.stack[0].lis_lvl == 1)
			ft_reverse_rotate_a(data);
		ft_optimal_reverse_push(data);
	}
}
