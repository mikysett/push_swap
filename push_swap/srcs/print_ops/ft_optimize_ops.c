/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimize_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:31 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 18:52:49 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_next_op(t_op_info *ops, int curr_pos, int nb_ops)
{
	curr_pos++;
	while (curr_pos < nb_ops)
	{
		if (ops[curr_pos].type != op_none)
			return (curr_pos);
		curr_pos++;
	}
	return (-1);
}

static int	ft_opti_push(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	next_ops[2];

	next_ops[0] = ft_next_op(ops, curr_pos, nb_ops);
	next_ops[1] = ft_next_op(ops, next_ops[0], nb_ops);
	if (next_ops[0] == -1 || next_ops[1] == -1)
		return (0);
	if (ops[curr_pos].type == op_rb
		&& ops[next_ops[0]].type == op_pb
		&& ops[next_ops[1]].type == op_rrb)
	{
		ops[curr_pos].type = op_pb;
		ops[next_ops[0]].type = op_sb;
		ops[next_ops[1]].type = op_none;
		return (next_ops[1] - curr_pos);
	}
	else if (ops[curr_pos].type == op_ra
		&& ops[next_ops[0]].type == op_pa
		&& ops[next_ops[1]].type == op_rra)
	{
		ops[curr_pos].type = op_pa;
		ops[next_ops[0]].type = op_sa;
		ops[next_ops[1]].type = op_none;
		return (next_ops[1] - curr_pos);
	}
	return (0);
}

void	ft_optimize_ops(t_op_info *ops, int nb_ops)
{
	int	i;

	i = -1;
	while (++i < nb_ops)
	{
		if (ops[i].type == op_none)
			continue;
		if (ops[i].type == op_pa || ops[i].type == op_pb)
			i += ft_opti_push(ops, i, nb_ops);
	}
}
