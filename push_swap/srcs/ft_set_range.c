/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 22:53:24 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"


void	ft_set_ranges(t_data *data)
{
	data->nb_ranges = ft_count_ranges(&data->s_a);
	data->ranges = ft_calloc(data->nb_ranges, sizeof(t_range));
	if (!data->ranges)
		ft_exit_failure();
	ft_set_sorted_range(data, &data->s_a);
	ft_set_unsorted_range(data, &data->s_a);

	DEBUG_CODE(
		ft_print_ranges(data);
		printf("RANGES SET FOR ALL UNSORTED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
	)
}

int	ft_count_ranges(t_stack *s)
{
	int		i;
	int		nb_ranges;
	t_nb	*prev_nb;

	nb_ranges = 0;
	prev_nb = 0;
	i = s->size;
	while (--i >= 0)
		if (s->stack[i].is_sorted)
		{
			if (!prev_nb || s->stack[i].sort_pos != prev_nb->sort_pos - 1)
			{
				s->stack[i].range = nb_ranges;
				nb_ranges++;
			}
			else
				s->stack[i].range = nb_ranges - 1;
			prev_nb = &s->stack[i];
		}
	return (nb_ranges);
}

void	ft_set_sorted_range(t_data *data, t_stack *s)
{
	int	i;
	int	curr_range;
	int	range_end;

	curr_range = 0;
	i = s->size;
	while (--i >= 0)
	{
		if (s->stack[i].is_sorted)
		{
			range_end = prev_sorted(&data->s_a, i - 1);
			if (s->stack[i].sort_pos == s->stack[range_end].sort_pos + 1)
				continue;
			data->ranges[curr_range].id = curr_range;
			data->ranges[curr_range].already_ranged = false;
			data->ranges[curr_range].nb_in_range = 0;
			data->ranges[curr_range].ind_start = i;
			data->ranges[curr_range].start_nb = s->stack[i].nb;
			data->ranges[curr_range].ind_end = range_end;
			data->ranges[curr_range].end_nb = s->stack[range_end].nb;
			curr_range++;
		}
	}
}

void	ft_set_unsorted_range(t_data *data, t_stack *s)
{
	int	i;

	i = 0;
	while (i < data->s_a.size)
	{
		if (!s->stack[i].is_sorted)
		{
			s->stack[i].range = ft_get_range(data, s->stack[i].nb);
			data->ranges[s->stack[i].range].nb_in_range++;
		}	
		i++;
	}
}

int	ft_get_range(t_data *data, int nb)
{
	int	i;
	
	i = 0;
	while (i < data->nb_ranges)
	{
		if (ft_is_in_range(&data->ranges[i], nb))
			return (i);
		i++;
	}
	return (-1);
}


bool	ft_is_in_range(t_range *range, int nb)
{
	if ((nb > range->start_nb && nb < range->end_nb)
		|| (range->start_nb > range->end_nb
			&& (nb > range->start_nb || nb < range->end_nb)))
		return (true);
	return (false);
}