/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/17 17:33:23 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_get_smallest_sort_pos(t_stack *s);

void	ft_rotate_sorted(t_data *data, t_stack *s, bool is_stack_a)
{
	int	curr_pos;
	int	smallest_sort_pos;

	curr_pos = -1;
	smallest_sort_pos = ft_get_smallest_sort_pos(s);
	while (++curr_pos < s->size)
		if (s->stack[curr_pos].sort_pos == smallest_sort_pos)
			break;
	if (curr_pos <= s->size / 2)
		while (curr_pos-- != 0)
			ft_reverse_rotate_stack(data, is_stack_a);
	else
	{
		curr_pos = s->size - curr_pos;
		while (curr_pos-- != 0)
			ft_rotate_stack(data, is_stack_a);
	}
}

static int	ft_get_smallest_sort_pos(t_stack *s)
{
	int	smallest_sort_pos;
	int	i;

	if (!s->size)
		return (0);
	smallest_sort_pos = s->stack[0].sort_pos;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].sort_pos < smallest_sort_pos)
			smallest_sort_pos = s->stack[i].sort_pos;
		i++;
	}
	return (smallest_sort_pos);
}
