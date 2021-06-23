/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opti_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:31 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:09:41 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_opti_push_three_ops(t_op_info *ops, int curr_pos, int*next);
static bool	ft_opti_push_five_ops(t_op_info *ops, int curr_pos, int*next);

bool	ft_opti_push(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	*next;

	next = ft_init_next(ops, curr_pos, nb_ops, 4);
	if ((next[1] != -1 && ft_opti_push_three_ops(ops, curr_pos, next))
		|| (next[3] != -1 && ft_opti_push_five_ops(ops, curr_pos, next)))
	{
		DEBUG_CODE(printf("ft_opti_push() applied!\n");)
		return (true);
	}
	return (false);
}

static bool	ft_opti_push_three_ops(t_op_info *ops, int curr_pos, int*next)
{
	if (ops[curr_pos].type == op_rb
		&& ops[next[0]].type == op_pb
		&& ops[next[1]].type == op_rrb)
	{
		ops[curr_pos].type = op_pb;
		ops[next[0]].type = op_sb;
		ops[next[1]].type = op_none;
		return (true);
	}
	else if (ops[curr_pos].type == op_ra
		&& ops[next[0]].type == op_pa
		&& ops[next[1]].type == op_rra)
	{
		ops[curr_pos].type = op_pa;
		ops[next[0]].type = op_sa;
		ops[next[1]].type = op_none;
		return (true);
	}
	return (false);
}

static bool	ft_opti_push_five_ops(t_op_info *ops, int curr_pos, int*next)
{
	if (ops[curr_pos].a_size <= 5 && ops[curr_pos].type == op_pb
		&& ops[next[0]].type == op_rra && ops[next[1]].type == op_rra
		&& ops[next[2]].type == op_pa && ops[next[3]].type == op_rra)
	{
		ops[curr_pos].type = op_sa;
		ops[next[0]].type = op_ra;
		ops[next[1]].type = op_sa;
		ops[next[2]].type = op_none;
		ops[next[3]].type = op_none;
		return (true);
	}
	else if (ops[curr_pos].a_size <= 5 && ops[curr_pos].type == op_pa
		&& ops[next[0]].type == op_rrb && ops[next[1]].type == op_rrb
		&& ops[next[2]].type == op_pb && ops[next[3]].type == op_rrb)
	{
		ops[curr_pos].type = op_sb;
		ops[next[0]].type = op_rb;
		ops[next[1]].type = op_sb;
		ops[next[2]].type = op_none;
		ops[next[3]].type = op_none;
		return (true);
	}
	return (false);
}
