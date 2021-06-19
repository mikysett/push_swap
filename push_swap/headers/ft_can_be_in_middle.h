/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_can_be_in_middle.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/17 18:28:30 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAN_BE_IN_MIDDLE_H
# define FT_CAN_BE_IN_MIDDLE_H

bool	ft_can_be_in_middle(int nb, t_nb *prev, t_nb *next);
t_nb	*ft_prev_in_lvl(t_stack *s, int pos, int lvl);
t_nb	*ft_next_in_lvl(t_stack *s, int pos, int lvl);


#endif
