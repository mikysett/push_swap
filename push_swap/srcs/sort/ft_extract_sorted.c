/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_sorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 23:16:12 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_extract_first_level(t_data *data, int sorting_level);
static int	ft_nb_sorted(t_stack *s, int sorting_level);
static void	ft_extract_sorting_level_from_a(t_data *data, int sorting_level);
static void	ft_extract_sorting_level_from_b(t_data *data, int sorting_level);

void	ft_extract_sorted(t_data *data)
{
	int	sorting_level;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	sorting_level = 2;
	ft_extract_first_level(data, sorting_level);
	ft_rotate_sorted(data, &data->s_a, true);
	sorting_level++;
	while (data->s_a.size_unsorted || data->s_b.size_unsorted)
	{
		if (data->s_a.size_unsorted)
			ft_extract_sorting_level_from_a(data, sorting_level);
		else
			ft_extract_sorting_level_from_b(data, sorting_level);
		sorting_level += 2;
	}
}

static void	ft_extract_first_level(t_data *data, int sorting_level)
{
	int	top;
	int	b_size;

	b_size = data->s_a.size - ft_nb_sorted(&data->s_a, sorting_level - 1);
	while (data->s_b.size != b_size)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].is_sorted == sorting_level)
		{
			ft_push_b(data);
			ft_rotate_b(data);
		}
		else if (data->s_a.stack[top].is_sorted != 1)
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
		}
		else
			ft_rotate_a(data);
	}
}

static int	ft_nb_sorted(t_stack *s, int sorting_level)
{
	int	i;
	int	nb_sorted;

	i = 0;
	nb_sorted = 0;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted == sorting_level)
			nb_sorted++;
		i++;
	}
	return (nb_sorted);
}

static void	ft_extract_sorting_level_from_a(t_data *data, int sorting_level)
{
	int	top;

	while (data->s_a.size_unsorted)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].is_sorted == sorting_level)
		{
			ft_rotate_a(data);
		}
		else if (data->s_a.stack[top].is_sorted == sorting_level + 1)
		{
			ft_push_b(data);
			ft_rotate_b(data);
		}
		else
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
		}
		data->s_a.size_unsorted--;
	}
}

static void	ft_extract_sorting_level_from_b(t_data *data, int sorting_level)
{
	int	top;

	while (data->s_b.size_unsorted)
	{
		top = data->s_b.size - 1;
		if (data->s_b.stack[top].is_sorted == sorting_level)
		{
			ft_rotate_b(data);
		}
		else if (data->s_b.stack[top].is_sorted == sorting_level + 1)
		{
			ft_push_a(data);
			ft_rotate_a(data);
		}
		else
		{
			ft_push_a(data);
			data->s_a.size_unsorted++;
		}
		data->s_b.size_unsorted--;
	}
}