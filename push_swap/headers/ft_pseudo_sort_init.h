/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_init.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 00:19:15 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PSEUDO_SORT_INIT_H
# define FT_PSEUDO_SORT_INIT_H

void	ft_init_ps_rec(t_ps_rec *rec, t_stack *s, int pos);
void	ft_init_ps_data(t_ps_data *ps_data, t_stack *s);
t_list	***ft_init_checks(int s_size);
t_ps	*ft_best_checked(t_list **checks, int s_size,
	int curr_pos, int initial_pos);
t_ps	*ft_abs_best_checked(t_list **checks);

#endif