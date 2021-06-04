/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimize_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:31 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 15:33:34 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_next_op(t_op_info *ops, int curr_pos, int nb_ops)
{
	if (curr_pos < 0)
		return (-1);
	curr_pos++;
	while (curr_pos < nb_ops)
	{
		if (ops[curr_pos].type != op_none)
			return (curr_pos);
		curr_pos++;
	}
	return (-1);
}

// static int	ft_opti_push(t_op_info *ops, int curr_pos, int nb_ops)
// {
// 	int	next[2];

// 	next[0] = ft_next_op(ops, curr_pos, nb_ops);
// 	next[1] = ft_next_op(ops, next[0], nb_ops);
// 	if (next[1] == -1)
// 		return (0);
// 	if (ops[curr_pos].type == op_rb
// 		&& ops[next[0]].type == op_pb
// 		&& ops[next[1]].type == op_rrb)
// 	{
// 		ops[curr_pos].type = op_pb;
// 		ops[next[0]].type = op_sb;
// 		ops[next[1]].type = op_none;
// 		DEBUG_CODE(printf("ft_opti_push() applied!\n");)
// 		return (next[1] - curr_pos);
// 	}
// 	else if (ops[curr_pos].type == op_ra
// 		&& ops[next[0]].type == op_pa
// 		&& ops[next[1]].type == op_rra)
// 	{
// 		ops[curr_pos].type = op_pa;
// 		ops[next[0]].type = op_sa;
// 		ops[next[1]].type = op_none;
// 		DEBUG_CODE(printf("ft_opti_push() applied!\n");)
// 		return (next[1] - curr_pos);
// 	}
// 	return (0);
// }


static int	ft_remove_useless(t_op_info *ops, int curr_pos,
	int nb_ops, bool *is_fine)
{
	int	next[1];

	next[0] = ft_next_op(ops, curr_pos, nb_ops);

	// PUSH case 1
	if (next[0] == -1)
		return (0);
	if ((ops[curr_pos].type == op_ra && ops[next[0]].type == op_rra)
		|| (ops[curr_pos].type == op_rra && ops[next[0]].type == op_ra)
		|| (ops[curr_pos].type == op_rb && ops[next[0]].type == op_rrb)
		|| (ops[curr_pos].type == op_rrb && ops[next[0]].type == op_rb)
		|| (ops[curr_pos].type == op_sa && ops[next[0]].type == op_sa)
		|| (ops[curr_pos].type == op_sb && ops[next[0]].type == op_sb)
		)
	{
		ops[curr_pos].type = op_none;
		ops[next[0]].type = op_none;
		DEBUG_CODE(printf("ft_remove_useless() applied!\n");)
		*is_fine = false;
		return (next[0] - curr_pos);
	}
	return (0);
}

static int	ft_opti_push(t_op_info *ops, int curr_pos, int nb_ops, bool *is_fine)
{
	int	next[4];

	next[0] = ft_next_op(ops, curr_pos, nb_ops);
	next[1] = ft_next_op(ops, next[0], nb_ops);
	next[2] = ft_next_op(ops, next[1], nb_ops);
	next[3] = ft_next_op(ops, next[2], nb_ops);

	// PUSH case 1
	if (next[1] == -1)
		return (0);
	if (ops[curr_pos].type == op_rb
		&& ops[next[0]].type == op_pb
		&& ops[next[1]].type == op_rrb)
	{
		ops[curr_pos].type = op_pb;
		ops[next[0]].type = op_sb;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_push() applied!\n");)
		*is_fine = false;
		return (next[1] - curr_pos);
	}
	else if (ops[curr_pos].type == op_ra
		&& ops[next[0]].type == op_pa
		&& ops[next[1]].type == op_rra)
	{
		ops[curr_pos].type = op_pa;
		ops[next[0]].type = op_sa;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_push() applied!\n");)
		*is_fine = false;
		return (next[1] - curr_pos);
	}
	// Push case 2
	if (next[3] == -1)
		return (0);
	if (ops[curr_pos].a_size <= 5 
		&& ops[curr_pos].type == op_pb
		&& ops[next[0]].type == op_rra
		&& ops[next[1]].type == op_rra
		&& ops[next[2]].type == op_pa
		&& ops[next[3]].type == op_rra)
	{
		ops[curr_pos].type = op_sa;
		ops[next[0]].type = op_ra;
		ops[next[1]].type = op_sa;
		ops[next[2]].type = op_none;
		ops[next[3]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rr() applied!\n");)
		*is_fine = false;
		return (next[3] - curr_pos);
	}
	else if (ops[curr_pos].a_size <= 5 
		&& ops[curr_pos].type == op_pa
		&& ops[next[0]].type == op_rrb
		&& ops[next[1]].type == op_rrb
		&& ops[next[2]].type == op_pb
		&& ops[next[3]].type == op_rrb)
	{
		ops[curr_pos].type = op_sb;
		ops[next[0]].type = op_rb;
		ops[next[1]].type = op_sb;
		ops[next[2]].type = op_none;
		ops[next[3]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rr() applied!\n");)
		*is_fine = false;
		return (next[3] - curr_pos);
	}
	return (0);
}

static int	ft_opti_rra(t_op_info *ops, int curr_pos, int nb_ops, bool *is_fine)
{
	int	next[5];

	next[0] = ft_next_op(ops, curr_pos, nb_ops);
	next[1] = ft_next_op(ops, next[0], nb_ops);
	next[2] = ft_next_op(ops, next[1], nb_ops);
	next[3] = ft_next_op(ops, next[2], nb_ops);
	next[4] = ft_next_op(ops, next[3], nb_ops);

	// PUSH case 1
	if (next[4] == -1)
		return (0);
	if (ops[curr_pos].a_size <= 5
		&& ops[curr_pos].type == op_rra
		&& ops[next[0]].type == op_rra
		&& ops[next[1]].type == op_pb
		&& ops[next[2]].type == op_rra
		&& ops[next[3]].type == op_rra
		&& ops[next[4]].type == op_pa)
	{
		ops[curr_pos].type = op_ra;
		ops[next[0]].type = op_pb;
		ops[next[1]].type = op_sa;
		ops[next[2]].type = op_pa;
		ops[next[3]].type = op_sa;
		ops[next[4]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rra() applied!\n");)
		*is_fine = false;
		return (next[1] - curr_pos);
	}
	return (0);
}

static int	ft_opti_ra(t_op_info *ops, int curr_pos, int nb_ops, bool *is_fine)
{
	int	next[2];

	next[0] = ft_next_op(ops, curr_pos, nb_ops);
	next[1] = ft_next_op(ops, next[0], nb_ops);

	if (next[1] == -1)
		return (0);
	if (ops[curr_pos].a_size == 3
		&& ops[curr_pos].type == op_ra
		&& ops[next[0]].type == op_sa
		&& ops[next[1]].type == op_rra)
	{
		ops[curr_pos].type = op_sa;
		ops[next[0]].type = op_ra;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_ra() applied!\n");)
		*is_fine = false;
		return (next[1] - curr_pos);
	}
	else if (ops[curr_pos].b_size != 3
		&& ops[curr_pos].type == op_rb
		&& ops[next[0]].type == op_sb
		&& ops[next[1]].type == op_rrb)
	{
		ops[curr_pos].type = op_sb;
		ops[next[0]].type = op_rb;
		ops[next[1]].type = op_none;
		DEBUG_CODE(printf("ft_opti_rb() applied!\n");)
		*is_fine = false;
		return (next[1] - curr_pos);
	}
	return (0);
}

void	ft_optimize_ops(t_op_info *ops, int nb_ops)
{
	int		i;
	bool	is_fine;

	i = -1;
	is_fine = true;
	while (++i < nb_ops)
	{
		if (ops[i].type == op_none)
			continue;
		ft_remove_useless(ops, i, nb_ops, &is_fine);
		if (ops[i].type == op_pa || ops[i].type == op_pb)
			i += ft_opti_push(ops, i, nb_ops, &is_fine);
	}
	i = -1;
	while (++i < nb_ops)
	{
		if (ops[i].type == op_none)
			continue;
		if (ops[i].type == op_rra)
			i += ft_opti_rra(ops, i, nb_ops, &is_fine);
		if (ops[i].type == op_ra || ops[i].type == op_rb)
			i += ft_opti_ra(ops, i, nb_ops, &is_fine);
	}
	if (!is_fine)
		ft_optimize_ops(ops, nb_ops);
}
