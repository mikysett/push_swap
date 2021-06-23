/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ops_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:31 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 22:54:07 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_next_op(t_op_info *ops, int curr_pos, int nb_ops);

int	*ft_init_next(t_op_info *ops, int curr_pos, int nb_ops, int nb_indexes)
{
	static int	next[OP_MAX_CHECK] = { -1 };
	int			i;

	next[0] = ft_next_op(ops, curr_pos, nb_ops);
	i = 1;
	while (i < nb_indexes)
	{
		next[i] = ft_next_op(ops, next[i - 1], nb_ops);
		i++;
	}
	return (next);
}

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
