/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_navigation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 12:38:59 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	prev_sorted(t_stack *s, int start_pos)
{
	while (start_pos >= 0 && !s->stack[start_pos].lis_lvl)
		start_pos--;
	return (start_pos);
}

int	next_sorted(t_stack *s, int start_pos)
{
	while (start_pos <= s->top && !s->stack[start_pos].lis_lvl)
		start_pos++;
	return (start_pos);
}

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
