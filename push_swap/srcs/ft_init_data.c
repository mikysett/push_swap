/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:33:19 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:17:24 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_alloc_data(t_data *data, int stack_size);
static void	ft_init_stacks(t_data *data, char **argv, int nb_items);
static void	ft_init_stack(t_stack *s, char **argv, int nb_items);

void	ft_init_data(int argc, char **argv, t_data *data)
{
	int		nb_items;
	char	**val_items;

	nb_items = argc - 1;
	val_items = argv + 1;
	ft_alloc_data(data, nb_items);
	ft_init_stacks(data, val_items, nb_items);
}

static void	ft_alloc_data(t_data *data, int stack_size)
{
	data->s_b.size = 0;
	data->s_a.stack = malloc(sizeof(t_nb) * stack_size);
	data->s_b.stack = malloc(sizeof(t_nb) * stack_size);
	if (!data->s_a.stack || !data->s_b.stack)
		ft_exit_failure();
}

static void	ft_init_stacks(t_data *data, char **val_items, int nb_items)
{
	ft_init_stack(&data->s_a, val_items, nb_items);
	ft_init_stack(&data->s_b, NULL, 0);
}

static void	ft_init_stack(t_stack *s, char **val_items, int nb_items)
{
	int	i;

	i = 0;
	s->size = nb_items;
	s->top = s->size - 1;
	s->lis_lvl = 0;
	while (--nb_items >= 0)
	{
		s->stack[nb_items].nb = ft_atoi(val_items[i]);
		s->stack[nb_items].init_pos = nb_items;
		s->stack[nb_items].lis_lvl = 0;
		s->stack[nb_items].range = 0;
		s->stack[nb_items].in_range = false;
		i++;
	}
}
