/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimal_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 02:04:15 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	ft_optimal_swap(t_data *data)
{
	if (data->s_b.size > 1 && data->s_a.size > 1
		&& data->s_a.stack[1].lis_lvl == 0
		&& data->s_b.stack[0].nb < data->s_b.stack[1].nb
		&& data->s_a.stack[0].nb > data->s_a.stack[1].nb)
		ft_swap_2(data);
	else
		return (false);
	return (true);
}

void	ft_optimal_reverse_push(t_data *data)
{
	t_nb	*first;
	t_nb	*last;

	last = &data->s_a.stack[data->s_a.top];
	first = &data->s_a.stack[0];
	while (first->lis_lvl != 1)
	{
		if (!first->lis_lvl && !last->lis_lvl && last > first)
			ft_push_b(data);
		else
		{
			ft_reverse_rotate_a(data);
			last = &data->s_a.stack[data->s_a.top];
		}
		first = &data->s_a.stack[0];
	}
}
