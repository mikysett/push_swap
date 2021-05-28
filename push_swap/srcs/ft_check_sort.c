/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/05/26 09:28:19 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_set_pos(t_stack *s, bool is_initial)
{
	int	i;

	i = 0;
	if (is_initial)
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

void	ft_set_sort_pos(t_stack *s, int low, int high)
{
	int	new_division;
	int	pivot;

	if (low >= high)
		return ;
	pivot = s->stack[high].nb;
	new_division = ft_partition(s, low, high, pivot);
	ft_set_sort_pos(s, low, new_division);
	ft_set_sort_pos(s, new_division + 1, high);
}

void	ft_fix_pos(t_stack *s)
{
	int		i;
	int		init_pos;
	t_nb	buf;

	i = 0;
	ft_set_pos(s, false);
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
