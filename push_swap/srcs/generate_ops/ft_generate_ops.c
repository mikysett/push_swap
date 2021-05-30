/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/05/30 17:54:19 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	ft_is_rotate_better(t_data *data)
{
	// To be implemented
	int	op_by_rotate;
	int	op_by_reverse;
	return (true);
}

bool	ft_optimal_swap(t_data *data)
{
	if (data->s_b.size > 1 && data->s_a.size > 1
		&& data->s_a.stack[1].is_sorted == false
		&& data->s_b.stack[0].nb < data->s_b.stack[1].nb
		&& data->s_a.stack[0].nb > data->s_a.stack[1].nb)
		ft_swap_2(data);
	else
		return (false);
	return (true);
}

void	ft_optimal_reverse_push(t_data *data)
{
	t_nb	*first;
	t_nb	*last;

	last = &data->s_a.stack[data->s_a.size - 1];
	first = &data->s_a.stack[0];
	while (first->is_sorted == false)
	{
		if (!first->is_sorted && last > first)
		{
			printf("orp - ");
			ft_push_b(data);
		}
		else
		{
			ft_reverse_rotate_a(data);
			last = &data->s_a.stack[data->s_a.size - 1];
		}
		first = &data->s_a.stack[0];
	}
}

void	ft_fill_b(t_data *data)
{
	int	last_nb;

	while (data->s_a.size &&
		data->s_a.stack[data->s_a.size - 1].is_sorted == false)
	{
		// printf("s_a[0].nb: %d, is sorted: %d\n",
		// 	data->s_a.stack[0].nb,
		// 	data->s_a.stack[0].is_sorted);
		// write(1, "fb - ", 5);
		ft_push_b(data);
		if (data->wait_to_swap == true)
			data->wait_to_swap = false;
		else if (ft_optimal_swap(data))
			data->wait_to_swap = true;
	}
	if (!data->s_a.size || data->nb_sorted == data->s_a.size)
		return ;
	if (ft_is_rotate_better(data))
		while (data->s_a.stack[data->s_a.size - 1].is_sorted == true)
			ft_rotate_a(data);
	else
	{
		while (data->s_a.stack[0].is_sorted == true)
			ft_reverse_rotate_a(data);
		ft_optimal_reverse_push(data);
	}
	ft_fill_b(data);
}

int		ft_best_to_sort(t_data *data)
{
	int	i;
	int	j;
	int	nb_sort_pos;

	i = 0;
	while (i < data->s_b.size)
	{
		nb_sort_pos = data->s_b.stack[i].sort_pos;
		j = 0;
		while (j < data->s_a.size)
		{
			// if ()
			j++;
		}
		i++;
	}
	// To be implemented
	return (0);
}

void	ft_sort_nb(t_data *data, int nb_i)
{
	// To be implemented

}

void	ft_sort_in_a(t_data *data)
{
	if (data->s_b.size == 0)
		return ;
	ft_sort_nb(data, ft_best_to_sort(data));
	ft_sort_in_a(data);
}

void	ft_rotate_sorted(t_data *data)
{
	int	bigger_nb_pos;
	int	curr_pos;

	curr_pos = -1;
	while (++curr_pos < data->s_a.size)
		if (data->s_a.stack[curr_pos].sort_pos == 0)
			break;
	if (curr_pos <= data->s_a.size / 2)
		while (curr_pos-- != 0)
			ft_reverse_rotate_a(data);
	else
		while (curr_pos-- != 0)
			ft_rotate_a(data);
}

void	ft_generate_ops(t_data *data)
{
	data->wait_to_swap = true;
	data->nb_moves = 0;
	ft_fill_b(data);
	ft_print_stack(&data->s_a);
	ft_print_stack(&data->s_b);
	printf("Nb moves: %d\n", data->nb_moves);
	ft_sort_in_a(data);
	ft_rotate_sorted(data);
	ft_flush_print_buffer();
}