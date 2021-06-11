/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/08 16:46:58 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

// bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos)
// {
// 	int	next;

// 	next = next_p(pos, step, s->size);
// 	if ((nb_sort_pos > s->stack[pos].sort_pos
// 		&& nb_sort_pos < s->stack[next].sort_pos)
// 		|| (nb_sort_pos > s->bigger_sort_pos
// 			&& s->stack[pos].sort_pos == s->bigger_sort_pos)
// 		|| (nb_sort_pos < s->smaller_sort_pos
// 			&& s->stack[next].sort_pos == s->smaller_sort_pos))
// 		return (true);
// 	// printf("STEP: %d  |  nb_sort_pos: %d  |  pos: %d\n", step, nb_sort_pos, pos);
// 	// if (nb_sort_pos > s->stack[pos].sort_pos
// 	// 	&& nb_sort_pos < s->stack[next].sort_pos)
// 	// {
// 	// 	printf("TRUE because nb_sort_pos in between the range\n");
// 	// 	return (true);
// 	// }
// 	// else if (nb_sort_pos > s->bigger_sort_pos
// 	// 		&& s->stack[pos].sort_pos == s->bigger_sort_pos)
// 	// {
// 	// 	printf("TRUE because nb_sort_pos is bigger than the bigger\n");
// 	// 	return (true);
// 	// }
// 	// else if (nb_sort_pos < s->smaller_sort_pos
// 	// 		&& s->stack[next].sort_pos == s->smaller_sort_pos)
// 	// {
// 	// 	printf("TRUE because nb_sort_pos is smaller than the smaller\n");
// 	// 	return (true);
// 	// }
// 	return (false);
// }


bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos)
{
	int	next;
	int	prev;

	prev = prev_sorted(s, pos - 1);
	next = next_sorted(s, pos);
	// DEBUG_CODE(printf("nb_sort_pos: %d, pos: %d, prev sort: %d, next_sort: %d\n", nb_sort_pos, pos, s->stack[prev].sort_pos, s->stack[next].sort_pos);)
	if (nb_sort_pos > s->stack[prev].sort_pos
		&& nb_sort_pos < s->stack[next].sort_pos)
	{
		// DEBUG_CODE(printf("true because in range\n");)
		return (true);
	}
	if (nb_sort_pos > s->bigger_sort_pos
			&& s->stack[prev].sort_pos == s->bigger_sort_pos)
	{
		// DEBUG_CODE(printf("true because bigger than bigger\n");)
		return (true);
	}
	if (nb_sort_pos < s->smaller_sort_pos
			&& s->stack[next].sort_pos == s->smaller_sort_pos)
	{
		// DEBUG_CODE(printf("true because smaller than smaller\n");)
		return (true);
	}
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

	i = data->s_a.size - 1;
	while (i != data->range.ind_start)
	{
		i_nb = data->s_a.stack[i].nb;
		if ((i_nb > data->range.start_nb && i_nb < data->range.end_nb)
		|| (i_nb > data->s_a.bigger_sort_pos
			&& data->range.start_nb == data->s_a.bigger_sort_pos)
		|| (i_nb < data->s_a.smaller_sort_pos
			&& data->range.end_nb == data->s_a.smaller_sort_pos))
			data->s_a.stack[i].in_range = true;
		i = prev_p(i, 1, data->s_a.size);
	}
}

static void ft_set_in_range_b(t_data *data)
{
	int	i;
	int	i_nb;

	i = 0;
	data->s_b.nb_in_range = 0;
	while (i != data->s_b.size)
	{
		i_nb = data->s_b.stack[i].nb;
		if ((i_nb > data->range.start_nb && i_nb < data->range.end_nb)
		|| (i_nb > data->s_b.bigger_sort_pos
			&& data->range.start_nb == data->s_b.bigger_sort_pos)
		|| (i_nb < data->s_b.smaller_sort_pos
			&& data->range.end_nb == data->s_b.smaller_sort_pos))
		{
			data->s_b.nb_in_range++;
			data->s_b.stack[i].in_range = true;
		}
		else
			data->s_b.stack[i].in_range = false;
		i++;
	}
}

// void	ft_organize_b(t_data *data)
// {
// 	t_stack	*s_b;
// 	int		top;
// 	int		top_a;
// 	int		org_by_rotate;
// 	int		org_by_reverse_rotate;
// 	int		i;
// 	int		first_in_range;
// 	int		last_in_range;



// 	s_b = &data->s_b;
// 	top = s_b->size - 1;
// 	i = top;
// 	while (!s_b->stack[i].in_range)
// 		i--;
// 	org_by_reverse_rotate = s_b->size - (top - i);
// 	i = 0;
// 	while (!s_b->stack[i].in_range)
// 		i++;
// 	org_by_rotate = s_b->size - i;
// 	if (org_by_rotate <= org_by_reverse_rotate)
// 	{
// 		while (org_by_rotate)
// 		{
// 			if (s_b->stack[top].in_range)
// 			{
// 				ft_push_a(data);
// 				top--;
// 			}
// 			else
// 			{
// 				ft_rotate_b(data);
// 			}
// 			org_by_rotate--;
// 		}
// 	}
// 	else
// 	{
// 		while (org_by_reverse_rotate)
// 		{
// 			ft_reverse_rotate_b(data);
// 			if (s_b->stack[top].in_range)
// 			{
// 				ft_push_a(data);
// 				top--;
// 			}
// 			else
// 			{
// 				ft_reverse_rotate_b(data);
// 			}
// 			org_by_reverse_rotate--;
// 		}
// 	}
// 	top_a = data->s_a.size - 1;
// 	while (data->s_a.stack[top_a].in_range)
// 	{
// 		ft_push_b(data);
// 		top_a--;
// 	}
// }

void	ft_organize_b(t_data *data)
{
	t_stack	*s_b;
	int		top_b;
	int		top_a;

	s_b = &data->s_b;
	top_b = s_b->size - 1;
	while (s_b->nb_in_range)
	{
		if (s_b->stack[top_b].in_range)
		{
			ft_push_a(data);
			top_b--;
			s_b->nb_in_range--;
		}
		else
			ft_rotate_b(data);
	}
	top_a = data->s_a.size - 1;
	while (data->s_a.stack[top_a].in_range)
	{
		ft_push_b(data);
		top_a--;
		s_b->nb_in_range++;
	}
}

static void	ft_set_range(t_data *data)
{
	data->range.ind_start = prev_sorted(&data->s_a, data->s_a.size - 1);
	data->range.ind_end = prev_sorted(&data->s_a, data->range.ind_start - 1);
	data->range.start_nb = data->s_a.stack[data->range.ind_start].nb;
	data->range.end_nb = data->s_a.stack[data->range.ind_end].nb;
	DEBUG_CODE(ft_print_data_range(data);)
	ft_set_in_range_a(data);
	ft_set_in_range_b(data);

	DEBUG_CODE(
		printf("--> AFTER FT SET RANGE\n");
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		// printf("Nb moves: %d\n", data->nb_moves);
	)
}

void	ft_generate_ops(t_data *data)
{
	int	s_full_size;

	s_full_size = data->s_a.size;
	DEBUG_CODE(printf("data->s_a.nb_sorted: %d\n", data->s_a.nb_sorted);)

	while (data->s_a.nb_sorted != s_full_size)
	{
		ft_set_range(data);
		ft_fill_b(data);
		ft_sort_in_a(data, true);
		if (data->s_a.nb_sorted != data->s_a.size)
			ft_goto_unsorted(data);
		else
			ft_sort_in_a(data, false);
	}

	DEBUG_CODE(
		printf("\nFINAL RESULT:\n");
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
	)
}
