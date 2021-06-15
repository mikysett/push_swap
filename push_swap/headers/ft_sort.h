/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/15 18:03:33 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

void		ft_sort(t_data *data);
int			prev_p(int pos, int step, int stack_size);
int			next_p(int pos, int step, int stack_size);
void		ft_extract_sorted(t_data *data, int sorting_level);
int			ft_nb_sorted(t_stack *s, int sorting_level);
void		ft_extract_sorting_level_from_a(t_data *data, int sorting_level);
void		ft_extract_sorting_level_from_b(t_data *data, int sorting_level);


static void	ft_rotate_sorted(t_data *data);

void	ft_sort_nb(t_data *data, t_nb *nb_ptr);
t_nb	*ft_best_to_sort(t_data *data, bool only_in_range);
#endif
