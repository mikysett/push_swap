/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:41:09 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_sort(t_data *data)
{
	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	ft_extract_sorted(data);
	ft_optimize_extracted(data);
	DEBUG_CODE(
		printf("EXTRACT SORTED COMPLETED\n");
		ft_print_stack_ligh(data);
		ft_print_ops(data, op_none);
		// ft_exit_failure();
	)
	ft_merge_sorted(data);
	ft_rotate_sorted(data, stack_a);
	DEBUG_CODE(
		printf("FINAL STATUS OF BOTH STACKS:\n");
		ft_print_stack_ligh(data);
		ft_print_ops(data, op_none);
		ft_exit_failure();
	)
	ft_print_ops(data, op_none);
}
