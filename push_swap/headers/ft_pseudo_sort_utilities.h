/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_utilities.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 00:45:05 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PSEUDO_SORT_UTILITIES_H
# define FT_PSEUDO_SORT_UTILITIES_H

void	ft_free_checks(t_list ***checks, int s_size);
void	ft_save_check(t_list **checks, t_ps *new);
void	ft_take_best(t_ps **best, t_ps **new);
void	ft_take_partial_best(t_ps **best, t_ps **new);
void	ft_set_is_sorted(t_stack *s, t_ps *ps);

#endif