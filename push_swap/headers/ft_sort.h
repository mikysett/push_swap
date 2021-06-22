/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/21 16:43:41 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

void		ft_sort(t_data *data);

void		ft_merge_sorted(t_data *data);
void		ft_compact_top(t_data *data, t_stack *s, bool is_stack_a);

void		ft_init_merge(t_data *data, t_merge_info *m);
void		ft_chose_best_top_lvl(t_data *data);
void		ft_chose_best_top_lvl_in_stack(t_data *data, t_stack *s,
				bool is_stack_a);
int			ft_get_lvl_size(t_stack *s, int sort_lvl);
void		ft_reverse_rotate_bottom_lvl(t_data *data, t_stack *s,
				bool is_stack_a);


bool		ft_any_reversed_in_stack(t_stack *s);

bool		ft_more_levels_in_a(t_data *data);
int			ft_count_lvl(t_stack *s);
bool		ft_top_level_reversed(t_stack *s, int pos);
bool		ft_bottom_level_reversed(t_stack *s, int pos);
void		ft_merge_into(t_data *data, t_merge_info *m);
bool		ft_merge_from_bottom(t_data *data, t_merge_info *m,
				int from_bottom_lvl);
void		ft_merge_reversed(t_data *data, t_merge_info *m);
void		ft_merge_tail(t_data *data, t_merge_info *m,
				int lvl_to_sort, int dest_lvl);

bool		ft_only_one_level(t_stack *s);
int			ft_get_biggest_nb(t_stack *s);
int			ft_get_smallest_nb(t_stack *s);
void		ft_update_tops(t_merge_info *m);

void		ft_invert_level(t_data *data, bool merge_into_a, t_stack *s);
void		ft_align_s_in(t_data *data, t_merge_info *m);

void		ft_rotate_sorted(t_data *data, t_stack *s, bool is_stack_a);

void		ft_sort_nb(t_data *data, t_nb *nb_ptr);
t_nb		*ft_best_to_sort(t_data *data, bool only_in_range);

#endif
