/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:33:19 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 18:55:14 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_alloc_data(t_data *data, int stack_size);
static void	ft_init_stack_a(t_data *data, char **argv, int nb_items);

void	ft_init_data(int argc, char **argv, t_data *data)
{
	int	nb_items;

	nb_items = argc - 1;
	ft_alloc_data(data, nb_items);
	data->s_a.sorting_level = 0;
	ft_init_stack_a(data, argv, nb_items);

}

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

static void	ft_init_stack_a(t_data *data, char **argv, int nb_items)
{
	int	j;

	j = 1;
	while (--nb_items >= 0)
	{
		data->s_a.stack[nb_items].nb = ft_atoi(argv[j]);
		data->s_a.stack[nb_items].init_pos = nb_items;
		data->s_a.stack[nb_items].is_sorted = 0;
		data->s_a.stack[nb_items].range = 0;
		data->s_a.stack[nb_items].in_range = false;
		j++;
	}
}
