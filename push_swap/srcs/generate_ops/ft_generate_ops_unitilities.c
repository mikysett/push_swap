/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops_unitilities.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 15:24:36 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	prev_sorted(t_stack *s, int start_pos)
{
	if (start_pos < 0)
		start_pos += s->size;
	while (!s->stack[start_pos].is_sorted)
	{
		start_pos--;
		if (start_pos < 0)
			start_pos = s->size - 1;
	}
	return (start_pos);
}

int	next_sorted(t_stack *s, int start_pos)
{
	if (start_pos >= s->size)
		start_pos -= s->size;
	while (!s->stack[start_pos].is_sorted)
	{
		start_pos++;
		if (start_pos == s->size)
			start_pos = 0;
	}
	return (start_pos);
}

int	ft_bigger(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}

int	ft_smaller(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb2);
	return (nb1);
}

int	ft_abs_diff(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb1 - nb2);
	return (nb2 - nb1);
}
