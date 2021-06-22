/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_can_be_in_middle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:04:07 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 14:14:40 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	ft_can_be_in_middle(int nb, t_nb *prev, t_nb *next)
{
	if (!prev && !next)
		return (true);
	if (!prev && next && nb < next->nb)
		return (true);
	if (prev && !next && nb > prev->nb)
		return (true);
	if (prev && next
		&& ((nb > prev->nb && nb < next->nb)
			|| (prev->nb > next->nb && nb > prev->nb)))
		return (true);
	return (false);
}

t_nb	*ft_prev_in_lvl(t_stack *s, int pos, int lvl)
{
	pos = (pos + 1) % s->size;
	while (s->stack[pos].lis_lvl != lvl)
		pos = (pos + 1) % s->size;
	return (&s->stack[pos]);
}

t_nb	*ft_next_in_lvl(t_stack *s, int pos, int lvl)
{
	pos--;
	if (pos < 0)
		pos = s->top;
	while (s->stack[pos].lis_lvl != lvl)
	{
		pos--;
		if (pos < 0)
			pos = s->top;
	}
	return (&s->stack[pos]);
}
