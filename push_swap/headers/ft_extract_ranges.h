/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_ranges.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 18:47:01 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTRACT_CHAGES_H
# define FT_EXTRACT_CHAGES_H

void	ft_extract_ranges(t_data *data);
void	ft_extract_from_unranged(t_data *data, int curr_range);
int		ft_get_eligible_items(t_data *data, int curr_range);
bool	ft_are_range_ordered(t_data *data, int curr_range);
void	ft_extract_unranged_chunk(t_data *data, int curr_range);
void	ft_range_buf_bottom(t_data *data, int range_to_take);

#endif
