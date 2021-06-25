/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 13:42:54 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_big_stack_sort(t_data *data);
static void	ft_small_stack_sort(t_data *data);

void	ft_sort(t_data *data)
{	
	if (data->s_a.size > 10)
		ft_big_stack_sort(data);
	else
		ft_small_stack_sort(data);

	ft_rotate_sorted(data, stack_a);
	DEBUG_CODE(ft_print_stack_ligh(data);)
	ft_print_ops(data, op_none);
}

static void	ft_big_stack_sort(t_data *data)
{
	ft_pseudo_sort(&data->s_a);
	DEBUG_CODE(
		printf("Stacks after pseudo sort\n");
		ft_print_stack_ligh(data);
	)
	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	ft_extract_sorted(data);
	ft_optimize_extracted(data);
	DEBUG_CODE(
		printf("EXTRACT SORTED COMPLETED\n");
		ft_print_stack_ligh(data);
		ft_print_ops(data, op_none);
	)
	ft_merge_sorted(data);
}

static void	ft_small_stack_sort(t_data *data)
{
	ft_circling_pseudo_sort(&data->s_a);
	DEBUG_CODE(
		printf("Stacks after circling pseudo sort\n");
		ft_print_stack_ligh(data);
	)
	data->wait_to_swap = true;
	ft_set_edge_sort_pos(&data->s_a);
	ft_fill_b(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
	ft_sort_in_a(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
}
