/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_sorted.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/18 15:41:13 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTRACT_SORTED_H
# define FT_EXTRACT_SORTED_H

void	ft_extract_sorted(t_data *data);
bool	ft_increment_lvl_by_swap(t_data *data, t_stack *s, int sort_lvl);

#endif
