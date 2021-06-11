/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 17:54:18 by msessa           ###   ########.fr       */
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
		printf("RANGES SET FOR ALL UNSORTED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
	)
}

int	ft_count_ranges(t_stack *s)
{
	int	i;
	int	nb_ranges;

	nb_ranges = 0;
	i = 0;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted)
			nb_ranges++;
		i++;
	}
	return (nb_ranges);
}

void	ft_set_sorted_range(t_data *data, t_stack *s)
{
	int	i;
	int	curr_range;
	int	range_end;

	curr_range = 0;
	i = s->size - 1;
	while (i >= 0)
	{
		if (s->stack[i].is_sorted)
		{
			data->ranges[curr_range].ind_start = i;
			data->ranges[curr_range].start_nb = s->stack[i].nb;
			range_end = prev_sorted(&data->s_a, i - 1);
			data->ranges[curr_range].ind_end = range_end;
			data->ranges[curr_range].end_nb = s->stack[range_end].nb;
			curr_range++;
		}
		i--;
	}
	
	DEBUG_CODE(ft_print_ranges(data);)
}

void	ft_set_unsorted_range(t_data *data, t_stack *s)
{
	int	i;

	i = 0;
	while (i < data->s_a.size)
	{
		if (!s->stack[i].is_sorted)
			s->stack[i].range = ft_get_range(data, s->stack[i].nb);
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