/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 19:35:25 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GENERATE_SORT_H
# define FT_GENERATE_SORT_H

bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos);
void	ft_generate_ops(t_data *data);

void	ft_flush_print_buffer(void);

int		prev_sorted(t_stack *s, int start_pos);
int		next_sorted(t_stack *s, int start_pos);
int		ft_bigger(int nb1, int nb2);
int		ft_smaller(int nb1, int nb2);
int		ft_abs_diff(int nb1, int nb2);

void	ft_sort_in_a(t_data *data, bool only_in_range);

void	ft_fill_b(t_data *data);

#endif
