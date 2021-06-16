/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 11:14:42 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_rotate(t_stack *s)
{
	int		top;
	t_nb	buf;

	if (s->size < 2)
		return (false);
	top = s->size - 1;
	buf = s->stack[top];
	while (top > 0)
	{
		s->stack[top] = s->stack[top - 1];
		top--;
	}
	s->stack[0] = buf;
	return (true);
}

void	ft_rotate_a(t_data *data)
{
	if (ft_rotate(&data->s_a))
		ft_print_ops(data, op_ra);
}

void	ft_rotate_b(t_data *data)
{
	if (ft_rotate(&data->s_b))
		ft_print_ops(data, op_rb);
}

void	ft_rotate_2(t_data *data)
{
	bool	res_ra;
	bool	res_rb;

	res_ra = ft_rotate(&data->s_a);
	res_rb = ft_rotate(&data->s_b);
	if (res_ra && res_rb)
		ft_print_ops(data, op_rr);
	else if (res_ra)
		ft_print_ops(data, op_ra);
	else if (res_rb)
		ft_print_ops(data, op_rb);
}

void	ft_rotate_stack(t_data *data, bool is_stack_a)
{
	if (is_stack_a)
		ft_rotate_a(data);
	else
		ft_rotate_b(data);
}
