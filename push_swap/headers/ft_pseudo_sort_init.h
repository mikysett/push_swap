/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_init.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/05/30 19:21:24 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PSEUDO_SORT_INIT_H
# define FT_PSEUDO_SORT_INIT_H

void	ft_init_ps_rec(t_ps_rec *rec, t_stack *s, bool circled, int pos);
void	ft_init_ps_data(t_ps_data *ps_data, t_stack *s);
t_ps	*ft_best_checked(t_list **checks, int circled, int first_nb);
t_ps	*ft_abs_best_checked(t_list **checks, bool *linear_v, bool *circled_v);

#endif