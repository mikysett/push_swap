/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lvl_manipulations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:59:23 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_swap_lvl(t_data *data, t_s_name dest, t_stack *s_from)
{
	int	level;

	if (s_from->top < 1)
		return ;
	level = s_from->stack[s_from->top].lis_lvl;
	while (s_from->size > 0 && s_from->stack[s_from->top].lis_lvl == level)
		ft_push_stack(data, dest);
}

void	ft_reverse_swap_lvl(t_data *data, t_s_name dest, t_stack *s_from)
{
	int	level;

	if (s_from->top < 1)
		return ;
	level = s_from->stack[0].lis_lvl;
	while (s_from->size > 0 && s_from->stack[0].lis_lvl == level)
	{
		ft_reverse_rotate_stack(data, ft_opposite_s(dest));
		ft_push_stack(data, dest);
	}
}
