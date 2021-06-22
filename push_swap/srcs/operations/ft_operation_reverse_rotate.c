/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_reverse_rotate.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:41 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 16:10:01 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_reverse_rotate(t_stack *s);

void	ft_reverse_rotate_stack(t_data *data, t_s_name s_name)
{
	if (s_name == stack_a)
		ft_reverse_rotate_a(data);
	else
		ft_reverse_rotate_b(data);
}

void	ft_reverse_rotate_a(t_data *data)
{
	if (ft_reverse_rotate(&data->s_a))
		ft_print_ops(data, op_rra);
}

void	ft_reverse_rotate_b(t_data *data)
{
	if (ft_reverse_rotate(&data->s_b))
		ft_print_ops(data, op_rrb);
}

void	ft_reverse_rotate_2(t_data *data)
{
	bool	res_rra;
	bool	res_rrb;

	res_rra = ft_reverse_rotate(&data->s_a);
	res_rrb = ft_reverse_rotate(&data->s_b);
	if (res_rra && res_rrb)
		ft_print_ops(data, op_rrr);
	else if (res_rra)
		ft_print_ops(data, op_rra);
	else if (res_rrb)
		ft_print_ops(data, op_rrb);
}

static bool	ft_reverse_rotate(t_stack *s)
{
	int 	i;
	t_nb	buf;

	if (s->size < 2)
		return (false);
	i = 1;
	buf = s->stack[0];
	while (i <= s->top)
	{
		s->stack[i - 1] = s->stack[i];
		i++;
	}
	s->stack[s->top] = buf;
	return (true);
}
