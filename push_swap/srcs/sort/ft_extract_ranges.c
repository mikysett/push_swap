/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_ranges.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:39:32 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 18:49:12 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_extract_ranges(t_data *data)
{
	int	curr_range;

	curr_range = 0;
	data->s_a.splitted_bottom_buf = false;
	while (data->s_a.nb_sorted != data->s_a.size)
	{
		ft_extract_unranged_from_a(data, curr_range);
		ft_extract_from_unranged(data, curr_range);
		ft_range_buf_bottom(data, curr_range, curr_range + 1);
		ft_realign_range(data, curr_range - 1);
		ft_extract_next_unranged(data, curr_range);
		if (data->s_a.nb_sorted != data->s_a.size)
		{
			ft_move_to_next_range(data, curr_range);
			curr_range++;
		}
		// if (curr_range == 20)
		// 	break;

		DEBUG_CODE(
			printf("--> FOR RANGE %d\n", curr_range - 1);
			printf("nb sorted in a: %d, a size: %d\n\n", data->s_a.nb_sorted,
				data->s_a.size);
			printf("Stack A:\n");
			ft_print_stack(&data->s_a);
			printf("Stack B:\n");
			ft_print_stack(&data->s_b);
			ft_print_ops(data, op_none);
			printf("data->s_b.nb_not_in_range: %d\n", data->s_b.nb_not_in_range);
			ft_print_stats(data);
			printf("END of RANGES SORT\n");
		)
	}

	DEBUG_CODE(
		// while (1)
		// {

		// }
	)
}

void	ft_extract_unranged_from_a(t_data *data, int curr_range)
{
	int	top;

	top = data->s_a.size - 1;
	while (!data->s_a.stack[top].is_sorted)
	{
		if (data->s_a.stack[top].range == curr_range)
		{
			ft_push_b(data);
			if (data->s_b.nb_not_in_range > 0)
			{
				ft_rotate_b(data);
				DEBUG_CODE(data->stats.fill_b++;)
			}
			DEBUG_CODE(data->stats.fill_b++;)
		}
		else if (data->s_a.stack[top].range == curr_range + 1)
		{
			ft_rotate_a(data);
			DEBUG_CODE(data->stats.fill_b++;)
		}
		else
		{
			ft_push_b(data);
			data->s_b.nb_not_in_range++;
			DEBUG_CODE(data->stats.fill_b++;)
		}
		top = data->s_a.size - 1;
	}
	if (data->s_a.stack[top].range == curr_range - 1)
	{
		ft_rotate_a(data);
		DEBUG_CODE(data->stats.fill_b++;)
		ft_extract_unranged_from_a(data, curr_range);
	}
}

void	ft_extract_from_unranged(t_data *data, int curr_range)
{
	int		top;
	int		nb_eligible_items;
	bool	range_ordered;

	top = data->s_b.size - 1;
	nb_eligible_items = ft_get_eligible_items(data, curr_range);
	range_ordered = false;
	if (!nb_eligible_items)
		return ;
	while (nb_eligible_items)
	{
		if (data->s_b.stack[top].range == curr_range)
		{
			ft_rotate_b(data);
			nb_eligible_items--;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		else if (data->s_b.stack[top].range == curr_range + 1)
		{
			if (!range_ordered)
				range_ordered = ft_range_ordered_in_b(data, curr_range);
			if (range_ordered)
			{
				ft_rotate_b(data);
				DEBUG_CODE(data->stats.reduce_not_in_range++;)
			}
			else
			{
				ft_push_a(data);
				// ft_rotate_a(data);
				data->s_a.unranged_in_buffer++;
				DEBUG_CODE(data->stats.reduce_not_in_range++;)
			}
			nb_eligible_items--;
		}
		else
		{
			ft_push_a(data);
			data->s_a.unranged_in_buffer++;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		data->s_b.nb_not_in_range--;
		top = data->s_b.size - 1;
	}
	// TODO implement dynamic fill of unranged +3 and +4 before to remerge
	// the two unranged (top of b stack and buffer on top on a stack)
	// while (data->s_a.unranged_in_buffer)
	// {
	// 	ft_push_b(data);
	// 	data->s_a.unranged_in_buffer--;
	// 	data->s_b.nb_not_in_range++;
	// 	DEBUG_CODE(data->stats.reduce_not_in_range++;)
	// }
}

int	ft_get_eligible_items(t_data *data, int curr_range)
{
	int	i;
	int	top;
	int	nb_eligible_items;

	i = 0;
	top = data->s_b.size - 1;
	nb_eligible_items = 0;
	while (i < data->s_b.nb_not_in_range)
	{
		if (data->s_b.stack[top - i].range == curr_range
			|| data->s_b.stack[top - i].range == curr_range + 1)
			nb_eligible_items++;
		i++;
	}
	return (nb_eligible_items);
}

bool	ft_range_ordered_in_b(t_data *data, int curr_range)
{
	int		i;
	int		top;
	bool	second_range_found;

	i = 0;
	top = data->s_b.size - 1;
	second_range_found = false;
	// printf("data->s_b.nb_not_in_range = %d\n", data->s_b.nb_not_in_range);
	// printf("data->s_b.size = %d\n", data->s_b.size);
	while (i < data->s_b.nb_not_in_range)
	{
		if (data->s_b.stack[top - i].range == curr_range + 1)
			second_range_found = true;
		else if (second_range_found
			&& data->s_b.stack[top - i].range == curr_range)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_range_ordered_in_a_chunk(t_data *data, int curr_range)
{
	int		i;
	int		top;
	bool	second_range_found;

	i = 0;
	top = data->s_a.size - 1;
	second_range_found = false;
	// printf("data->s_b.nb_not_in_range = %d\n", data->s_b.nb_not_in_range);
	// printf("data->s_b.size = %d\n", data->s_b.size);
	while (i < data->s_a.unranged_in_buffer)
	{
		if (data->s_a.stack[top - i].range == curr_range + 1)
			second_range_found = true;
		else if (second_range_found
			&& data->s_a.stack[top - i].range == curr_range)
			return (false);
		i++;
	}
	return (true);
}

// void	ft_range_buf_bottom(t_data *data, int curr_range, int range_to_take)
// {
// 	int	top;
// 	int	nb_to_revert;

// 	nb_to_revert = 0;
// 	while (data->s_a.stack[0].range == range_to_take
// 		&& !data->s_a.stack[0].is_sorted)
// 	{
// 		ft_reverse_rotate_a(data);
// 		ft_push_b(data);
// 		ft_rotate_b(data);
// 		DEBUG_CODE(data->stats.reduce_not_in_range += 3;)
// 	}
// 	// Second condition should not be necessary... buggy thing and lazy fix
// 	if (data->s_a.splitted_bottom_buf
// 		&& data->s_a.nb_sorted != data->s_a.size)
// 	{
// 		while (data->s_a.stack[0].is_sorted)
// 		{
// 			nb_to_revert++;
// 			ft_reverse_rotate_a(data);
// 			DEBUG_CODE(data->stats.reduce_not_in_range++;)
// 		}
// 		data->s_a.splitted_bottom_buf = false;
// 		ft_range_buf_bottom(data, curr_range, range_to_take);
// 		while (nb_to_revert--)
// 		{
// 			ft_rotate_a(data);
// 			DEBUG_CODE(data->stats.reduce_not_in_range++;)
// 		}
// 	}
// }

void	ft_range_buf_bottom(t_data *data, int curr_range, int range_to_take)
{
	while (data->s_a.stack[0].range == range_to_take
		&& !data->s_a.stack[0].is_sorted)
	{
		ft_reverse_rotate_a(data);
		ft_push_b(data);
		ft_rotate_b(data);
		DEBUG_CODE(data->stats.reduce_not_in_range += 3;)
	}
	if (data->s_a.stack[0].is_sorted
		&& data->s_a.stack[0].range == curr_range - 1)
	{
		ft_reverse_rotate_a(data);
		ft_range_buf_bottom(data, curr_range, range_to_take);
		DEBUG_CODE(data->stats.reduce_not_in_range++;)
	}
}

void	ft_realign_range(t_data *data, int range_to_align)
{
	int	top;

	top = data->s_a.size - 1;
	while (data->s_a.stack[top].range == range_to_align
		&& data->s_a.stack[top].is_sorted)
	{
		ft_rotate_a(data);
		DEBUG_CODE(data->stats.reduce_not_in_range++;)
	}
}

void	ft_extract_next_unranged(t_data *data, int curr_range)
{
	bool	range_1_in_a_chunk;
	bool	range_2_in_a_chunk;

	// ft_put_range_in_buf_bottom(data, curr_range + 2);
	// range_1_in_a_chunk = ft_is_range_in_a_chunk(data, curr_range + 1);
	// range_2_in_a_chunk = ft_is_range_in_a_chunk(data, curr_range + 2);
	ft_extract_next_unranged_from_a_chunk(data, curr_range);
}

void	ft_put_range_in_buf_bottom(t_data *data, int range_sel)
{
	int	nb_eligible_sgl_item;
	int	top;

	nb_eligible_sgl_item = ft_get_eligible_sgl_items(data, range_sel);
	while (nb_eligible_sgl_item)
	{
		top = data->s_b.size - 1;
		if (data->s_b.stack[top].range == range_sel)
		{
			ft_push_a(data);
			ft_rotate_a(data);
			nb_eligible_sgl_item--;
			data->s_a.splitted_bottom_buf = true;
			DEBUG_CODE(data->stats.reduce_not_in_range += 2;)
		}
		else
		{
			ft_push_a(data);
			data->s_a.unranged_in_buffer++;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		data->s_b.nb_not_in_range--;
	}
}


int	ft_get_eligible_sgl_items(t_data *data, int range_sel)
{
	int	i;
	int	top;
	int	nb_eligible_items;

	i = 0;
	top = data->s_b.size - 1;
	nb_eligible_items = 0;
	while (i < data->s_b.nb_not_in_range)
	{
		if (data->s_b.stack[top - i].range == range_sel)
			nb_eligible_items++;
		i++;
	}
	return (nb_eligible_items);
}

bool	ft_is_range_in_a_chunk(t_data *data, int range_sel)
{
	int	i;
	printf("ft_is_range_in_a_chunk: range_sel: %d \n", range_sel);
	i = data->s_a.size - 1 - data->s_a.unranged_in_buffer;
	while (i >= 0 && data->s_a.stack[i].is_sorted)
		i--;
	while (i >= 0 && !data->s_a.stack[i].is_sorted)
	{
		if (data->s_a.stack[i].range == range_sel)
			return (true);
		i--;
	}
	return (false);
}

void	ft_extract_next_unranged_from_a_chunk(t_data *data, int curr_range)
{
	int		top;

	while (data->s_a.unranged_in_buffer)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].range == curr_range + 1)
		{
			ft_push_b(data);
			ft_rotate_b(data);
			DEBUG_CODE(data->stats.reduce_not_in_range += 2;)
		}
		else if (data->s_a.stack[top].range == curr_range + 2)
		{
			data->s_a.splitted_bottom_buf = true;
			ft_rotate_a(data);
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		else
		{
			ft_push_b(data);
			data->s_b.nb_not_in_range++;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		data->s_a.unranged_in_buffer--;
	}
}

// Works only if there is unsorted numbers in between ranges
void	ft_move_to_next_range(t_data *data, int curr_range)
{
	int	top;

	top = data->s_a.size - 1;
	while (data->s_a.stack[top].is_sorted
		&& data->s_a.stack[top].range == curr_range)
	{
		ft_rotate_a(data);
		DEBUG_CODE(data->stats.fill_b++;)
	}
}
