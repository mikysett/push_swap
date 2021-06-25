/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_stack_sort.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 02:04:30 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SMALL_STACK_SORT_H
# define FT_SMALL_STACK_SORT_H

void	ft_generate_ops(t_data *data);
void	ft_set_edge_sort_pos(t_stack *s);

void	ft_sort_in_a(t_data *data);
t_nb	ft_best_to_sort(t_data *data);
void	ft_mov_align_a(t_nb *nb, t_stack *s, int nb_sort_pos);
void	ft_set_mov_to_sort(t_nb *nb);

void	ft_sort_nb(t_data *data, t_nb nb);

void	ft_set_nb_mov_to_top(t_nb *nb, int nb_pos, int s_size);
int		ft_bigger_nb(int nb1, int nb2);
int		ft_smaller_nb(int nb1, int nb2);
int		ft_abs_diff_nb(int nb1, int nb2);

void	ft_fill_b(t_data *data);
void	ft_update_edge_sort_pos(t_stack *s, int nb_index);
bool	ft_possible_sort_by_top(t_stack *s, int nb_sort_pos,
			int start, bool recursive);
bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos);
bool	ft_is_rotate_better(t_data *data);

bool	ft_optimal_swap(t_data *data);
void	ft_optimal_reverse_push(t_data *data);

int		prev_sorted(t_stack *s, int start_pos);
int		next_sorted(t_stack *s, int start_pos);
int		prev_p(int pos, int step, int stack_size);
int		next_p(int pos, int step, int stack_size);


#endif
