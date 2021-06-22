/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_sorted.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 21:16:54 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTRACT_SORTED_H
# define FT_EXTRACT_SORTED_H

void	ft_extract_sorted(t_data *data);
bool	ft_expand_lvl_by_swap(t_data *data, t_stack *s, int lis_lvl);
void	ft_init_stacks_name(t_data *data, t_merge_info *m);

#endif
