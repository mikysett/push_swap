/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimize_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:31 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 22:55:59 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	ft_remove_useless(t_op_info *ops, int curr_pos, int nb_ops);
static bool	ft_merge_ops(t_op_info *ops, int curr_pos, int nb_ops);
static bool	ft_opti_rra(t_op_info *ops, int curr_pos, int nb_ops);
static int	ft_opti_ra(t_op_info *ops, int curr_pos, int nb_ops);

void	ft_optimize_ops(t_op_info *ops, int nb_ops)
{
	int		i;
	bool	need_to_repass;

	i = -1;
	need_to_repass = false;
	while (++i < nb_ops)
	{
		if (ops[i].type == op_none)
			continue;
		ft_remove_useless(ops, i, nb_ops);
		ft_merge_ops(ops, i, nb_ops);
		if (ops[i].type == op_pa || ops[i].type == op_pb)
			need_to_repass = ft_opti_push(ops, i, nb_ops) || need_to_repass;
		else if (ops[i].type == op_rra)
			need_to_repass = ft_opti_rra(ops, i, nb_ops) || need_to_repass;
		else if (ops[i].type == op_ra || ops[i].type == op_rb)
			need_to_repass = ft_opti_ra(ops, i, nb_ops) || need_to_repass;
	}
	if (need_to_repass)
		ft_optimize_ops(ops, nb_ops);
}

static bool	ft_remove_useless(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	*next;

	next = ft_init_next(ops, curr_pos, nb_ops, 1);
	if (next[0] == -1)
		return (false);
	if ((ops[curr_pos].type == op_ra && ops[next[0]].type == op_rra)
		|| (ops[curr_pos].type == op_rra && ops[next[0]].type == op_ra)
		|| (ops[curr_pos].type == op_rb && ops[next[0]].type == op_rrb)
		|| (ops[curr_pos].type == op_rrb && ops[next[0]].type == op_rb)
		|| (ops[curr_pos].type == op_sa && ops[next[0]].type == op_sa)
		|| (ops[curr_pos].type == op_sb && ops[next[0]].type == op_sb)
		|| (ops[curr_pos].type == op_pa && ops[next[0]].type == op_pb)
		|| (ops[curr_pos].type == op_pb && ops[next[0]].type == op_pa)
		)
	{
		ops[curr_pos].type = op_none;
		ops[next[0]].type = op_none;
		DEBUG_CODE(printf("ft_remove_useless() applied!\n");)
		return (true);
	}
	return (false);
}

static bool	ft_merge_ops(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	*next;

	next = ft_init_next(ops, curr_pos, nb_ops, 1);
	if (next[0] == -1)
		return (false);
	if ((ops[curr_pos].type == op_sa && ops[next[0]].type == op_sb)
		|| (ops[curr_pos].type == op_sb && ops[next[0]].type == op_sa)
		|| (ops[curr_pos].type == op_ra && ops[next[0]].type == op_rb)
		|| (ops[curr_pos].type == op_rb && ops[next[0]].type == op_ra)
		|| (ops[curr_pos].type == op_rra && ops[next[0]].type == op_rrb)
		|| (ops[curr_pos].type == op_rrb && ops[next[0]].type == op_rra))
	{
		DEBUG_CODE(printf("ft_merge_ops() applied!\n");)
		if (ops[curr_pos].type == op_sa || ops[curr_pos].type == op_sb)		
			ops[curr_pos].type = op_ss;
		else if (ops[curr_pos].type == op_ra || ops[curr_pos].type == op_rb)
			ops[curr_pos].type = op_rr;
		else if (ops[curr_pos].type == op_rra || ops[curr_pos].type == op_rrb)
			ops[curr_pos].type = op_rrr;
		ops[next[0]].type = op_none;
		return (true);
	}
	return (false);
}

static bool	ft_opti_rra(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	*next;

	next = ft_init_next(ops, curr_pos, nb_ops, 5);
	if (next[4] == -1)
		return (false);
	if (ops[curr_pos].a_size <= 5
		&& ops[curr_pos].type == op_rra && ops[next[0]].type == op_rra
		&& ops[next[1]].type == op_pb && ops[next[2]].type == op_rra
		&& ops[next[3]].type == op_rra && ops[next[4]].type == op_pa)
	{
		ops[curr_pos].type = op_ra;
		ops[next[0]].type = op_pb;
		ops[next[1]].type = op_sa;
		ops[next[2]].type = op_pa;
		ops[next[3]].type = op_sa;
		ops[next[4]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rra() applied!\n");)
		return (true);
	}
	return (false);
}

static int	ft_opti_ra(t_op_info *ops, int curr_pos, int nb_ops)
{
	int	*next;

	next = ft_init_next(ops, curr_pos, nb_ops, 2);
	if (next[1] == -1)
		return (false);
	if (ops[curr_pos].a_size == 3 && ops[curr_pos].type == op_ra
		&& ops[next[0]].type == op_sa && ops[next[1]].type == op_rra)
	{
		ops[curr_pos].type = op_sa;
		ops[next[0]].type = op_ra;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_ra() applied!\n");)
		return (true);
	}
	else if (ops[curr_pos].b_size == 3 && ops[curr_pos].type == op_rb
		&& ops[next[0]].type == op_sb && ops[next[1]].type == op_rrb)
	{
		ops[curr_pos].type = op_sb;
		ops[next[0]].type = op_rb;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rb() applied!\n");)
		return (true);
	}
	return (false);
}
