/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 13:09:17 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_RANGE_H
# define FT_SET_RANGE_H

void	ft_set_ranges(t_data *data);
int		ft_count_ranges(t_stack *s);
void	ft_set_sorted_range(t_data *data, t_stack *s);
void	ft_set_unsorted_range(t_data *data, t_stack *s);
int		ft_get_range(t_data *data, int nb);
bool	ft_is_in_range(t_range *range, int nb);

#endif
