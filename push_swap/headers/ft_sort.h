/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 23:06:14 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

void		ft_sort(t_data *data);

void		ft_merge_sorted(t_data *data);
bool		ft_more_levels_in_a(t_data *data);
int			ft_count_lvl(t_stack *s);
bool		ft_level_reversed(t_stack *s);
void		ft_merge_into(t_data *data, bool merge_into_a,
				t_stack *s_in, t_stack *s_from);
bool		ft_only_one_level(t_stack *s);
int			ft_get_biggest_nb(t_stack *s);
void		ft_invert_level(t_data *data, bool merge_into_a, t_stack *s);

void		ft_rotate_sorted(t_data *data, t_stack *s, bool is_stack_a);

void		ft_sort_nb(t_data *data, t_nb *nb_ptr);
t_nb		*ft_best_to_sort(t_data *data, bool only_in_range);

#endif
