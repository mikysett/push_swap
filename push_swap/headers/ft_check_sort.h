/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_sort.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:00:45 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECK_SORT_H
# define FT_CHECK_SORT_H

void	ft_set_pos(t_stack *s, t_pos_type pos_type);
void	ft_set_sort_pos(t_data *data);
void	ft_sort_stack(t_stack *s, int low, int high);
void	ft_revert_to_initial_pos(t_stack *s);

#endif