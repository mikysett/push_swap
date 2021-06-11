/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_ranges.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:39:32 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 18:56:11 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_extract_ranges(t_data *data)
{
	int	top;
	int	curr_range;

	curr_range = 0;
	top = data->s_a.size - 1;
	while (data->s_a.nb_sorted != data->s_a.size)
	{
		ft_extract_unranged_chunk(data, curr_range);
		ft_extract_from_unranged(data, curr_range);
		ft_range_buf_bottom(data, curr_range + 2);
		curr_range++;
		ft_rotate_a(data);
		DEBUG_CODE(data->stats.fill_b++;)
	}

	DEBUG_CODE(
		printf("--> AFTER EXTRACTING RANGES\n");
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		printf("data->s_b.nb_not_in_range: %d\n", data->s_b.nb_not_in_range);
		ft_print_stats(data);
		while (1)
		{

		}
	)
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
		if (data->s_b.stack[top].range == curr_range + 1)
		{
			ft_rotate_b(data);
			data->s_b.nb_not_in_range--;
			nb_eligible_items--;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		else if (data->s_b.stack[top].range == curr_range + 2)
		{
			if (!range_ordered)
				range_ordered = ft_are_range_ordered(data, curr_range);
			if (range_ordered)
			{
				ft_rotate_b(data);
				DEBUG_CODE(data->stats.reduce_not_in_range++;)
			}
			else
			{
				ft_push_a(data);
				ft_rotate_a(data);
				DEBUG_CODE(data->stats.reduce_not_in_range += 2;)
			}
			data->s_b.nb_not_in_range--;
			nb_eligible_items--;
		}
		else
		{
			ft_push_a(data);
			data->s_b.unranged_in_buffer++;
			data->s_b.nb_not_in_range--;
			DEBUG_CODE(data->stats.reduce_not_in_range++;)
		}
		top = data->s_b.size - 1;
	}
	// TODO implement dynamic fill of unranged +3 and +4 before to remerge
	// the two unranged (top of b stack and buffer on top on a stack)
	while (data->s_b.unranged_in_buffer)
	{
		ft_push_b(data);
		data->s_b.unranged_in_buffer--;
		data->s_b.nb_not_in_range++;
		DEBUG_CODE(data->stats.reduce_not_in_range++;)
	}
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
		if (data->s_b.stack[top - i].range == curr_range + 1
			|| data->s_b.stack[top - i].range == curr_range + 2)
			nb_eligible_items++;
		i++;
	}
	return (nb_eligible_items);
}

bool	ft_are_range_ordered(t_data *data, int curr_range)
{
	int		i;
	int		top;
	bool	second_range_found;

	i = 0;
	top = data->s_b.size - 1;
	second_range_found = false;
	printf("data->s_b.nb_not_in_range = %d\n", data->s_b.nb_not_in_range);
	printf("data->s_b.size = %d\n", data->s_b.size);
	while (i < data->s_b.nb_not_in_range)
	{
		if (data->s_b.stack[top - i].range == curr_range + 2)
			second_range_found = true;
		else if (second_range_found
			&& data->s_b.stack[top - i].range == curr_range + 1)
			return (false);
		i++;
	}
	return (true);
}

void	ft_extract_unranged_chunk(t_data *data, int curr_range)
{
	int	top;

	top = data->s_a.size - 1;
	while (!data->s_a.stack[top].is_sorted)
	{
		if (data->s_a.stack[top].range == curr_range + 1)
		{
			ft_push_b(data);
			if (data->s_b.nb_not_in_range > 0)
			{
				ft_rotate_b(data);
				DEBUG_CODE(data->stats.fill_b++;)
			}
			DEBUG_CODE(data->stats.fill_b++;)
		}
		else if (data->s_a.stack[top].range == curr_range + 2)
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
}

void	ft_range_buf_bottom(t_data *data, int range_to_take)
{
	while (data->s_a.stack[0].range == range_to_take
		&& !data->s_a.stack[0].is_sorted)
	{
		ft_reverse_rotate_a(data);
		ft_push_b(data);
		ft_rotate_b(data);
		DEBUG_CODE(data->stats.fill_b += 3;)
	}
}
