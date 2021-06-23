/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:25:32 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_reverse_five(t_data *data, t_s_name s_name);
static void	ft_reverse_many(t_data *data, t_stack *s, t_s_name s_name);

void	ft_reverse_stack(t_data *data, t_stack *s, t_s_name s_name)
{
	if (s->size < 2)
		return ;
	if (s->size == 2)
		ft_rotate_stack(data, s_name);
	else if (s->size == 3)
	{
		ft_rotate_stack(data, s_name);
		ft_swap_stack(data, s_name);
	}
	else if (s->size == 4)
	{
		ft_swap_stack(data, s_name);
		ft_rotate_stack(data, s_name);
		ft_rotate_stack(data, s_name);
		ft_swap_stack(data, s_name);
	}
	else if (s->size == 5)
		ft_reverse_five(data, s_name);
	else
		ft_reverse_many(data, s, s_name);
}

static void	ft_reverse_five(t_data *data, t_s_name s_name)
{
	ft_swap_stack(data, s_name);
	ft_reverse_rotate_stack(data, s_name);
	ft_push_stack(data, ft_opposite_s(s_name));
	ft_reverse_rotate_stack(data, s_name);
	ft_reverse_rotate_stack(data, s_name);
	ft_swap_stack(data, s_name);
	ft_push_stack(data, s_name);
}

static void	ft_reverse_many(t_data *data, t_stack *s, t_s_name s_name)
{
	int	pushes_to_do;
	int	i;

	pushes_to_do = s->size - 2;
	i = pushes_to_do;
	while (i-- > 0)
		ft_push_stack(data, ft_opposite_s(s_name));
	ft_rotate_stack(data, s_name);
	i = pushes_to_do;
	while (i-- > 0)
	{
		ft_push_stack(data, s_name);
		ft_rotate_stack(data, s_name);
	}
}
