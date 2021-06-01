/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_swap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 13:19:33 by msessa           ###   ########.fr       */
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
	int	size_a;
	int	size_b;

	ft_swap_a(data);
	ft_swap_b(data);
	size_a = data->s_a.size;
	size_b = data->s_b.size;
	if (size_a && size_b)
	{
		ft_print_ops(data, op_ss);
		data->nb_moves++;
	}
	else if (size_a)
	{
		ft_print_ops(data, op_sa);
		data->nb_moves++;
	}
	else if (size_b)
	{
		ft_print_ops(data, op_sb);
		data->nb_moves++;
	}
}
