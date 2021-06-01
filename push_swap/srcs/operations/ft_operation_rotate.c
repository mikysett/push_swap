/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 13:15:01 by msessa           ###   ########.fr       */
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
	{
		ft_print_ops(data, op_ra);
		// write(1, "ra\n", 3);
		data->nb_moves++;
	}
}

void	ft_rotate_b(t_data *data)
{
	if (ft_rotate(&data->s_b))
	{
		ft_print_ops(data, op_rb);
		// write(1, "rb\n", 3);
		data->nb_moves++;
	}
}

void	ft_rotate_2(t_data *data)
{
	bool	res_ra;
	bool	res_rb;

	res_ra = ft_rotate(&data->s_a);
	res_rb = ft_rotate(&data->s_b);
	if (res_ra && res_rb)
	{
		ft_print_ops(data, op_rr);
		data->nb_moves++;
	}
	else if (res_ra)
	{
		ft_print_ops(data, op_ra);
		data->nb_moves++;
	}
	else if (res_rb)
	{
		ft_print_ops(data, op_rb);
		data->nb_moves++;
	}
}
