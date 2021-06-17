/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/17 00:24:45 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_push(t_stack *s_in, t_stack *s_out);

void	ft_push_stack(t_data *data, bool is_stack_a)
{
	if (is_stack_a)
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

static bool	ft_push(t_stack *s_in, t_stack *s_out)
{
	int	top_in;
	int	top_out;

	if (s_out->size < 1)
		return (false);
	top_in = s_in->size;
	top_out = s_out->size - 1;
	s_in->stack[top_in] = s_out->stack[top_out];
	s_in->size++;
	s_out->size--;
	return (true);
}
