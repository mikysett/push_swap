/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:42:57 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 13:39:58 by msessa           ###   ########.fr       */
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
# include "ft_check_sort.h"
# include "ft_checks_utilities.h"
# include "ft_pseudo_sort_init.h"
# include "ft_pseudo_sort_utilities.h"
# include "ft_pseudo_sort.h"

# include "ft_operation_swap.h"
# include "ft_operation_push.h"
# include "ft_operation_rotate.h"
# include "ft_operation_reverse_rotate.h"


# include "ft_sort.h"
# include "ft_extract_ranges.h"
# include "ft_set_range.h"
# include "ft_print_ops.h"
# include "ft_generate_ops.h"

# include "ft_tests.h"

void	ft_init_data(int argc, char **argv, t_data *data);

void	ft_free_data(t_data *data);
void	ft_exit_failure(void);

#endif
