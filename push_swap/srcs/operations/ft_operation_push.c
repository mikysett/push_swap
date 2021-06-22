/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 16:10:01 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_push(t_stack *s_in, t_stack *s_out);

void	ft_push_stack(t_data *data, t_s_name s_name)
{
	if (s_name == stack_a)
		ft_push_a(data);
	else
		ft_push_b(data);
}

void	ft_push_a(t_data *data)
{
	if (ft_push(&data->s_a, &data->s_b))
		ft_print_ops(data, op_pa);
}

void	ft_push_b(t_data *data)
{
	if (ft_push(&data->s_b, &data->s_a))
		ft_print_ops(data, op_pb);
}

static bool	ft_push(t_stack *s_in, t_stack *s_from)
{
	if (s_from->size < 1)
		return (false);
	s_in->stack[s_in->top + 1] = s_from->stack[s_from->top];
	s_in->size++;
	s_from->size--;
	s_in->top++;
	s_from->top--;
	return (true);
}
