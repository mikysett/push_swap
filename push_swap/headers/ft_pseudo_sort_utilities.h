/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_utilities.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/15 16:38:52 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PSEUDO_SORT_UTILITIES_H
# define FT_PSEUDO_SORT_UTILITIES_H

void	ft_free_sgl_check(void *void_ps);
void	ft_free_checks(t_list ***checks, int s_size);
void	ft_save_check(t_list **checks, t_ps *new);
void	ft_set_is_sorted(t_stack *s, t_ps *ps);
int		ft_chunk_size(int size, int pos, int first_pos);
bool	ft_all_sorted_set(t_stack *s);

#endif