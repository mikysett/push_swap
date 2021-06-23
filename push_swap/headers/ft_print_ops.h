/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ops.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 22:55:25 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_OPS
# define FT_PRINT_OPS

void	ft_print_ops(t_data *data, t_op_type op_type);
void	ft_optimize_ops(t_op_info *ops, int nb_ops);
int		*ft_init_next(t_op_info *ops, int curr_pos, int nb_ops, int nb_indexes);
bool	ft_opti_push(t_op_info *ops, int curr_pos, int nb_ops);


#endif