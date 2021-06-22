/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 16:10:01 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_rotate(t_stack *s);

void	ft_rotate_stack(t_data *data, t_s_name s_name)
{
	if (s_name == stack_a)
		ft_rotate_a(data);
	else
		ft_rotate_b(data);
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

static bool	ft_rotate(t_stack *s)
{
	int		curr_top;
	t_nb	buf;

	if (s->size < 2)
		return (false);
	curr_top = s->top;
	buf = s->stack[curr_top];
	while (curr_top > 0)
	{
		s->stack[curr_top] = s->stack[curr_top - 1];
		curr_top--;
	}
	s->stack[0] = buf;
	return (true);
}
