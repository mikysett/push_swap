/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:31:29 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:23:10 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_print(t_op_info *ops, int nb_to_print);
static void	ft_print_sgl_op(t_op_type type);
static void	ft_align_ops(t_op_info *ops);

void	ft_print_ops(t_data *data, t_op_type op_type)
{
	static int			nb_ops = 0;
	static t_op_info	ops[OP_BUF_SIZE] = {(t_op_info){.type = op_none,
		.a_size = 0, .b_size = 0}};

	if (op_type == op_none)
	{
		ft_optimize_ops(ops, nb_ops);
		ft_print(ops, nb_ops);
		nb_ops = 0;
		return ;
	}
	ops[nb_ops].type = op_type;
	ops[nb_ops].a_size = data->s_a.size;
	ops[nb_ops].b_size = data->s_b.size;
	nb_ops++;
	if (nb_ops == OP_BUF_SIZE)
	{
		ft_optimize_ops(ops, nb_ops);
		ft_print(ops, OP_BUF_SIZE - OP_SUB_BUF);
		ft_align_ops(ops);
		nb_ops = OP_SUB_BUF;
	}
}

static void	ft_print(t_op_info *ops, int nb_to_print)
{
	int	i;

	DEBUG_CODE(static int	nb_ops = 0;)
	i = 0;
	while (i < nb_to_print)
	{
		DEBUG_CODE(
			if (ops[i].type != op_none)
				nb_ops++;
			i++;
			continue;
		)
		if (ops[i].type != op_none)
			ft_print_sgl_op(ops[i].type);
		i++;
	}
	DEBUG_CODE(
		printf("nb_ops: %d\n", nb_ops);
	)
}

static void	ft_print_sgl_op(t_op_type type)
{
	static char	ops_str[12][4] = {
		"",
		"sa\n",
		"sb\n",
		"ss\n",
		"pa\n",
		"pb\n",
		"ra\n",
		"rb\n",
		"rr\n",
		"rra\n",
		"rrb\n",
		"rrr\n"
	};
	static int	ops_str_size[12] = {0, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4};

	write(1, ops_str[type], ops_str_size[type]);
}

static void	ft_align_ops(t_op_info *ops)
{
	int	i;
	int	step;

	i = 0;
	step = OP_BUF_SIZE - OP_SUB_BUF;
	while (i < OP_SUB_BUF)
	{
		ops[i] = ops[i + step];
		i++;
	}
}
