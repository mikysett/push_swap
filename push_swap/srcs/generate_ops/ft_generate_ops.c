/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/07 15:27:23 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos)
{
	int	next_p_i;

	next_p_i = next_p(pos, step, s->size);
	if ((nb_sort_pos > s->stack[pos].sort_pos
		&& nb_sort_pos < s->stack[next_p_i].sort_pos)
		|| (nb_sort_pos > s->bigger_sort_pos
			&& s->stack[pos].sort_pos == s->bigger_sort_pos)
		|| (nb_sort_pos < s->smaller_sort_pos
			&& s->stack[next_p_i].sort_pos == s->smaller_sort_pos))
		return (true);
	return (false);
}

static void	ft_goto_unsorted(t_data *data)
{
	// if (ft_is_rotate_better(data))
		while (data->s_a.stack[data->s_a.size - 1].is_sorted == 1)
			ft_rotate_a(data);
	// else
	// {
	// 	while (data->s_a.stack[0].is_sorted == 1)
	// 		ft_reverse_rotate_a(data);
	// 	ft_optimal_reverse_push(data);
	// }
}

static void ft_set_in_range_a(t_data *data)
{
	int	i;
	int	i_nb;

	i = next_p(data->range.ind_start, 1, data->s_a.size);
	while (i != data->range.ind_end)
	{
		i_nb = data->s_a.stack[i].nb;
		if ((i_nb > data->range.start_nb && i_nb < data->range.end_nb)
		|| (i_nb > data->s_a.bigger_sort_pos
			&& data->range.start_nb == data->s_a.bigger_sort_pos)
		|| (i_nb < data->s_a.smaller_sort_pos
			&& data->range.end_nb == data->s_a.smaller_sort_pos))
			data->s_a.stack[i].in_range = true;
		i = next_p(i, 1, data->s_a.size);
	}
}

static void ft_set_in_range_b(t_data *data)
{
	int	i;
	int	i_nb;

	i = 0;
	while (i != data->s_b.size)
	{
		i_nb = data->s_b.stack[i].nb;
		if ((i_nb > data->range.start_nb && i_nb < data->range.end_nb)
		|| (i_nb > data->s_b.bigger_sort_pos
			&& data->range.start_nb == data->s_b.bigger_sort_pos)
		|| (i_nb < data->s_b.smaller_sort_pos
			&& data->range.end_nb == data->s_b.smaller_sort_pos))
			data->s_b.stack[i].in_range = true;
		else
			data->s_b.stack[i].in_range = false;
		i++;
	}
}

static void	ft_set_range(t_data *data)
{
	data->range.ind_start = prev_sorted(&data->s_a, data->s_a.size - 1);
	data->range.ind_end = prev_sorted(&data->s_a, data->range.ind_start - 1);
	data->range.start_nb = data->s_a.stack[data->range.ind_start].nb;
	data->range.end_nb = data->s_a.stack[data->range.ind_end].nb;
	ft_set_in_range_a(data);
	ft_set_in_range_b(data);
}

void	ft_generate_ops(t_data *data)
{
	DEBUG_CODE(printf("data->s_a.nb_sorted: %d\n", data->s_a.nb_sorted);)

	DEBUG_CODE(
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		// printf("Nb moves: %d\n", data->nb_moves);
	)
	while (data->s_a.nb_sorted != data->s_a.size)
	{
		ft_set_range(data);
		ft_fill_b(data);
		ft_sort_in_a(data);
		if (data->s_a.nb_sorted != data->s_a.size)
			ft_goto_unsorted(data);
	}
	DEBUG_CODE(
		printf("\nFINAL RESULT:\n");
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		// printf("Nb moves: %d\n", data->nb_moves);
	)
}
