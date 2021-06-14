/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 19:01:56 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

void	ft_sort(t_data *data);
int		prev_p(int pos, int step, int stack_size);
int		next_p(int pos, int step, int stack_size);

void	ft_sort_nb(t_data *data, t_nb *nb_ptr);
t_nb	*ft_best_to_sort(t_data *data, bool only_in_range);
#endif
