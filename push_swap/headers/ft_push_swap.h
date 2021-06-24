/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:42:57 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 18:52:27 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft/libft.h"
# include "ft_types.h"

# include "ft_parser.h"
# include "ft_init_data.h"
# include "ft_check_sort.h"
# include "ft_checks_utilities.h"
# include "ft_pseudo_sort_init.h"
# include "ft_pseudo_sort_utilities.h"
# include "ft_remove_checks.h"
# include "ft_pseudo_sort.h"
# include "ft_circling_pseudo_sort.h"

# include "ft_operation_swap.h"
# include "ft_operation_push.h"
# include "ft_operation_rotate.h"
# include "ft_operation_reverse_rotate.h"

# include "ft_sort.h"
# include "ft_small_stack_sort.h"
# include "ft_extract_sorted.h"
# include "ft_can_be_in_middle.h"
# include "ft_optimize_extracted.h"
# include "ft_reverse_stack.h"
# include "ft_print_ops.h"

# include "ft_tests.h"

void	ft_free_data(t_data *data);
void	ft_exit_failure(void);

#endif
