/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_utilities.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 16:43:40 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECKS_UTILITIES_H
# define FT_CHECKS_UTILITIES_H

void	ft_take_best(t_ps **best, t_ps **new);
t_ps	*ft_best_checked(t_list **checks, int s_size, int pos, int first_pos);
t_ps	*ft_abs_best_checked(t_list **checks);

#endif