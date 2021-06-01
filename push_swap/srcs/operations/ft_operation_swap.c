/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_swap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 17:24:59 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_swap(t_stack *s)
{
	int		top;
	t_nb	buf;

	if (s->size < 2)
		return (false);
	top = s->size - 1;
	buf = s->stack[top];
	s->stack[top] = s->stack[top - 1];
	s->stack[top - 1] = buf;
	return (true);
}

void	ft_swap_a(t_data *data)
{
	if (ft_swap(&data->s_a))
	{
		ft_print_ops(data, op_sa);
		// write(1, "sa\n", 3);
		data->nb_moves++;
	}
}

void	ft_swap_b(t_data *data)
{
	if (ft_swap(&data->s_b))
	{
		ft_print_ops(data, op_sb);
		// write(1, "sb\n", 3);
		data->nb_moves++;
	}
}

void	ft_swap_2(t_data *data)
{
	bool	res_sa;
	bool	res_sb;

	res_sa = ft_swap(&data->s_a);
	res_sb = ft_swap(&data->s_b);
	if (res_sa && res_sb)
	{
		ft_print_ops(data, op_ss);
		data->nb_moves++;
	}
	else if (res_sa)
	{
		ft_print_ops(data, op_sa);
		data->nb_moves++;
	}
	else if (res_sb)
	{
		ft_print_ops(data, op_sb);
		data->nb_moves++;
	}
}
