/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/17 00:30:24 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_reverse_five(t_data *data, bool is_stack_a);
static void	ft_reverse_many(t_data *data, t_stack *s, bool is_stack_a);

void	ft_reverse_stack(t_data *data, t_stack *s, bool is_stack_a)
{
	if (s->size < 2)
		return ;
	if (s->size == 2)
		ft_rotate_stack(data, is_stack_a);
	else if (s->size == 3)
	{
		ft_rotate_stack(data, is_stack_a);
		ft_swap_stack(data, is_stack_a);
	}
	else if (s->size == 4)
	{
		ft_swap_stack(data, is_stack_a);
		ft_rotate_stack(data, is_stack_a);
		ft_rotate_stack(data, is_stack_a);
		ft_swap_stack(data, is_stack_a);
	}
	else if (s->size == 5)
		ft_reverse_five(data, is_stack_a);
	else
		ft_reverse_many(data, s, is_stack_a);
}

static void	ft_reverse_five(t_data *data, bool is_stack_a)
{
	ft_swap_stack(data, is_stack_a);
	ft_reverse_rotate_stack(data, is_stack_a);
	ft_push_stack(data, !is_stack_a);
	ft_reverse_rotate_stack(data, is_stack_a);
	ft_reverse_rotate_stack(data, is_stack_a);
	ft_swap_stack(data, is_stack_a);
	ft_push_stack(data, is_stack_a);
}

static void	ft_reverse_many(t_data *data, t_stack *s, bool is_stack_a)
{
	int	pushes_to_do;
	int	i;

	pushes_to_do = s->size - 2;
	i = pushes_to_do;
	while (i-- > 0)
		ft_push_stack(data, !is_stack_a);
	ft_rotate_stack(data, is_stack_a);
	i = pushes_to_do;
	while (i-- > 0)
	{
		ft_push_stack(data, is_stack_a);
		ft_rotate_stack(data, is_stack_a);
	}
}