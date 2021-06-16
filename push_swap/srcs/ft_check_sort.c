/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 18:59:08 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_partition(t_stack *s, int low, int high, int pivot);

void	ft_set_pos(t_stack *s, t_pos_type pos_type)
{
	int	i;

	i = 0;
	if (pos_type == initial_pos)
		while (i < s->size)
		{
			s->stack[i].init_pos = i;
			i++;
		}
	else
		while (i < s->size)
		{
			s->stack[i].sort_pos = i;
			i++;
		}
}

void	ft_set_sort_pos(t_data *data)
{
	ft_sort_stack(&data->s_a, 0, data->s_a.size - 1);
	if (ft_duplicated_nb(&data->s_a))
		ft_exit_failure();
	ft_set_pos(&data->s_a, sorted_pos);
	ft_revert_to_initial_pos(&data->s_a);
}

void	ft_sort_stack(t_stack *s, int low, int high)
{
	int	new_division;
	int	pivot;

	if (low >= high)
		return ;
	pivot = s->stack[high].nb;
	new_division = ft_partition(s, low, high, pivot);
	ft_sort_stack(s, low, new_division);
	ft_sort_stack(s, new_division + 1, high);
}

static int	ft_partition(t_stack *s, int low, int high, int pivot)
{
	t_nb	buf;
	int		i;
	int		curr_pos;

	i = high;
	curr_pos = high;
	while (i >= low)
	{
		if (s->stack[i].nb < pivot)
		{
			if (i != curr_pos)
			{
				buf = s->stack[i];
				s->stack[i] = s->stack[curr_pos];
				s->stack[curr_pos] = buf;
			}
			curr_pos--;
		}
		i--;
	}
	if (curr_pos == high)
		return (curr_pos - 1);
	return (curr_pos);
}

void	ft_revert_to_initial_pos(t_stack *s)
{
	int		i;
	int		init_pos;
	t_nb	buf;

	i = 0;
	while (i < s->size)
	{
		if (s->stack[i].init_pos != i)
		{
			init_pos = s->stack[i].init_pos;
			buf = s->stack[init_pos];
			s->stack[init_pos] = s->stack[i];
			s->stack[i] = buf;
		}
		else
			i++;
	}
}
