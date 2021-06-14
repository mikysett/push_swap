/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:33:19 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 19:33:34 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"


static void	ft_alloc_data(t_data *data, int stack_size)
{
	data->s_a.size = stack_size;
	data->s_b.size = 0;
	data->s_a.stack = malloc(sizeof(t_nb) * stack_size);
	data->s_b.stack = malloc(sizeof(t_nb) * stack_size);
	if (!data->s_a.stack || !data->s_b.stack)
		ft_exit_failure();
	DEBUG_CODE(
		data->stats.fill_b = 0;
		data->stats.sort_not_in_range = 0;
		data->stats.reduce_not_in_range = 0;
		data->stats.organize_not_in_range = 0;
		data->stats.merge_stacks = 0;
		data->stats.rotate_sorted = 0;
	)
}

void	ft_init_data(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	i = argc - 1;
	ft_alloc_data(data, i);
	data->ranges = 0;
	data->s_a.sorting_level = 0;
	data->s_a.nb_not_in_range = 0;
	data->s_a.unranged_in_buffer = 0;
	data->s_b.nb_not_in_range = 0;
	data->s_b.unranged_in_buffer = 0;
	while (--i >= 0)
	{
		data->s_a.stack[i].nb = ft_atoi(argv[j]);
		data->s_a.stack[i].init_pos = i;
		data->s_a.stack[i].is_sorted = 0;
		data->s_a.stack[i].range = 0;

		// TODO clean this code if necessary
		data->s_a.stack[i].in_range = false;
		j++;
	}
}
