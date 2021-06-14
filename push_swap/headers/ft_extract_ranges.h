/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_ranges.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 18:33:33 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTRACT_CHAGES_H
# define FT_EXTRACT_CHAGES_H

void	ft_extract_ranges(t_data *data);
void	ft_extract_unranged_from_a(t_data *data, int curr_range);
void	ft_extract_from_unranged(t_data *data, int curr_range);
int		ft_get_eligible_items(t_data *data, int curr_range);
bool	ft_range_ordered_in_b(t_data *data, int curr_range);
bool	ft_range_ordered_in_a_chunk(t_data *data, int curr_range);
void	ft_range_buf_bottom(t_data *data, int curr_range, int range_to_take);
void	ft_realign_range(t_data *data, int range_to_align);
void	ft_extract_next_unranged(t_data *data, int curr_range);
void	ft_put_range_in_buf_bottom(t_data *data, int range_sel);
int		ft_get_eligible_sgl_items(t_data *data, int range_sel);
bool	ft_is_range_in_a_chunk(t_data *data, int range_sel);
void	ft_extract_next_unranged_from_a_chunk(t_data *data, int curr_range);
void	ft_move_to_next_range(t_data *data, int curr_range);

#endif
