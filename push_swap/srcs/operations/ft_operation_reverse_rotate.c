/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_reverse_rotate.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 17:21:14 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_reverse_rotate(t_stack *s)
{
	int 	i;
	int		top;
	t_nb	buf;

	if (s->size < 2)
		return (false);
	i = 1;
	top = s->size - 1;
	buf = s->stack[0];
	while (i <= top)
	{
		s->stack[i - 1] = s->stack[i];
		i++;
	}
	s->stack[top] = buf;
	return (true);
}

void	ft_reverse_rotate_a(t_data *data)
{
	if (ft_reverse_rotate(&data->s_a))
	{
		ft_print_ops(data, op_rra);
		// write(1, "rra\n", 4);
		data->nb_moves++;
	}
}

void	ft_reverse_rotate_b(t_data *data)
{
	if (ft_reverse_rotate(&data->s_b))
	{
		ft_print_ops(data, op_rrb);
		// write(1, "rrb\n", 4);
		data->nb_moves++;
	}
}

void	ft_reverse_rotate_2(t_data *data)
{
	bool	res_rra;
	bool	res_rrb;

	res_rra = ft_reverse_rotate(&data->s_a);
	res_rrb = ft_reverse_rotate(&data->s_b);
	if (res_rra && res_rrb)
	{
		ft_print_ops(data, op_rrr);
		// write(1, "rrr\n", 4);
		data->nb_moves++;
	}
	else if (res_rra)
	{
		ft_print_ops(data, op_rra);
		// write(1, "rra\n", 4);
		data->nb_moves++;
	}
	else if (res_rrb)
	{
		ft_print_ops(data, op_rrb);
		// write(1, "rrb\n", 4);
		data->nb_moves++;
	}
}
