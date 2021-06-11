/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:33:19 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 14:04:06 by msessa           ###   ########.fr       */
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
}

void	ft_init_data(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	i = argc - 1;
	ft_alloc_data(data, i);
	data->s_a.sorting_level = 0;
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
