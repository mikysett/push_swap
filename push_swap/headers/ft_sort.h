/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 16:48:38 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

void		ft_sort(t_data *data);

t_s_name	ft_opposite_s(t_s_name current_stack);
void		ft_init_stacks_name(t_data *data, t_merge_info *m);

int			ft_count_lvl(t_stack *s);
bool		ft_only_one_lvl(t_stack *s);
int			ft_get_lvl_size(t_stack *s, int lis_lvl);

void		ft_swap_lvl(t_data *data, t_s_name dest, t_stack *s_from);
void		ft_reverse_swap_lvl(t_data *data, t_s_name dest, t_stack *s_from);

t_s_name	ft_stack_with_less_lvl(t_data *data);
bool		ft_top_lvl_reversed(t_stack *s, int pos);
bool		ft_bottom_lvl_reversed(t_stack *s, int pos);
bool		ft_any_reversed_lvl_in_stack(t_stack *s);

void		ft_init_merge(t_data *data, t_merge_info *m);

void		ft_merge_into(t_data *data, t_merge_info *m);
void		ft_merge_tail(t_data *data, t_merge_info *m,
				int lvl_to_sort, int dest_lvl);
void		ft_align_s_in(t_data *data, t_merge_info *m);

void		ft_merge_reversed(t_data *data, t_merge_info *m);

bool		ft_merge_from_bottom(t_data *data, t_merge_info *m);

void		ft_merge_sorted(t_data *data);
void		ft_compact_top(t_data *data, t_stack *s, t_s_name s_name);

void		ft_rotate_sorted(t_data *data, t_s_name s_name);

// void		ft_sort_nb(t_data *data, t_nb *nb_ptr);
// t_nb		*ft_best_to_sort(t_data *data, bool only_in_range);

#endif
