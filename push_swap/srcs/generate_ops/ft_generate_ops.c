/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 13:29:27 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	ft_is_rotate_better(t_data *data)
{
	int	i;
	// To be implemented
	int	op_by_rotate;
	int	op_by_reverse;
	// return (true);
	op_by_rotate = 0;
	i = 0;
	while (data->s_a.stack[i].is_sorted)
		i++;
	op_by_reverse = i + 1;
	i = data->s_a.size - 1;
	while (i != op_by_reverse - 1)
	{
		if (data->s_a.stack[i].is_sorted)
			op_by_rotate++;
		else
			op_by_rotate = 0;
		i--;
	}
	if (op_by_rotate < op_by_reverse)
	{
		DEBUG_CODE(printf("by rotate\n");)
		return (true);
	}
	DEBUG_CODE(printf("BY REVERSE ROTATE\n");)
	return (false);
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
		if (!first->is_sorted && !last->is_sorted && last > first)
		{
			DEBUG_CODE(printf("orp - ");)
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

int	prev_sorted(t_stack *s, int start_pos)
{
	while (!s->stack[start_pos].is_sorted)
		start_pos--;
	return (start_pos);
}

int	next_sorted(t_stack *s, int start_pos)
{
	while (!s->stack[start_pos].is_sorted)
		start_pos++;
	return (start_pos);
}

void	ft_fill_b(t_data *data)
{
	int	prev_sorted_i;
	int	next_sorted_i;

	while (data->s_a.size &&
		data->s_a.stack[data->s_a.size - 1].is_sorted == false)
	{
		// printf("s_a[0].nb: %d, is sorted: %d\n",
		// 	data->s_a.stack[0].nb,
		// 	data->s_a.stack[0].is_sorted);
		// write(1, "fb - ", 5);
		prev_sorted_i = prev_sorted(&data->s_a, data->s_a.size - 3);
		next_sorted_i = next_sorted(&data->s_a, 1);
		if (data->s_a.stack[data->s_a.size - 2].is_sorted == true
				&& ft_is_sort_pos(&data->s_a,
					data->s_a.size - 2 - prev_sorted_i,
					data->s_a.stack[data->s_a.size - 1].sort_pos,
					prev_sorted_i))
		{
			data->nb_sorted++;
			data->s_a.stack[data->s_a.size - 1].is_sorted = true;
			if (data->s_a.stack[data->s_a.size - 1].sort_pos > data->s_a.bigger_sort_pos)
				data->s_a.bigger_sort_pos = data->s_a.stack[data->s_a.size - 1].sort_pos;
			else if (data->s_a.stack[data->s_a.size - 1].sort_pos < data->s_a.smaller_sort_pos)
				data->s_a.smaller_sort_pos = data->s_a.stack[data->s_a.size - 1].sort_pos;
			// if (!ft_optimal_swap(data))
				ft_swap_a(data);
			ft_fill_b(data);
			return ;
		}
		else if (data->s_a.stack[0].is_sorted == true
				&& ft_is_sort_pos(&data->s_a,
					next_sorted_i,
					data->s_a.stack[data->s_a.size - 1].sort_pos,
					0))
		{
			data->nb_sorted++;
			data->s_a.stack[data->s_a.size - 1].is_sorted = true;
			if (data->s_a.stack[data->s_a.size - 1].sort_pos > data->s_a.bigger_sort_pos)
				data->s_a.bigger_sort_pos = data->s_a.stack[data->s_a.size - 1].sort_pos;
			else if (data->s_a.stack[data->s_a.size - 1].sort_pos < data->s_a.smaller_sort_pos)
				data->s_a.smaller_sort_pos = data->s_a.stack[data->s_a.size - 1].sort_pos;
			// if (!ft_optimal_swap(data))
			ft_reverse_rotate_a(data);
			ft_swap_a(data);
			ft_fill_b(data);
			return ;
		}

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

void	ft_mov_align_a(t_nb *nb, t_stack *s, int nb_sort_pos)
{
	int	top;
	int	down;

	top = s->size - 1;
	down = 0;
	nb->strat.a_r = 0;
	nb->strat.a_rr = 1;
	DEBUG_CODE(
		printf("smaller sort pos: %d\n", s->smaller_sort_pos);
		printf("bigger sort pos: %d\n", s->bigger_sort_pos);
		printf("nb sort pos: %d\n", nb_sort_pos);
	)
	// while (s->stack[top].sort_pos < nb_sort_pos
	// 		|| (s->stack[next_p(top, 1, s->size)].sort_pos < nb_sort_pos
	// 			&& s->stack[next_p(top, 1, s->size)].sort_pos != s->size - 1))
	while (!ft_is_sort_pos(s, 1, nb_sort_pos, top))
	{
		nb->strat.a_r++;
		top--;
		DEBUG_CODE(printf("top: %d\n", top);)
	}
	// while (s->stack[down].sort_pos > nb_sort_pos
	// 		|| s->stack[prev_p(down, 1, s->size)].sort_pos < nb_sort_pos)
	while (!ft_is_sort_pos(s, 1, nb_sort_pos, down))
	{
		nb->strat.a_rr++;
		down++;
		DEBUG_CODE(printf("down\n");)
	}
}

void	ft_mov_to_top(t_nb *nb, int nb_pos, int s_size)
{
	nb->strat.b_r = s_size - 1 - nb_pos;
	nb->strat.b_rr = nb_pos + 1;
}

int	ft_bigger_nb(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}

int	ft_smaller_nb(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb2);
	return (nb1);
}

int	ft_abs_diff_nb(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb1 - nb2);
	return (nb2 - nb1);
}

void	ft_set_mov_to_sort(t_nb *nb)
{
	if (ft_bigger_nb(nb->strat.b_r, nb->strat.a_r)
		< ft_bigger_nb(nb->strat.b_rr, nb->strat.a_rr))
	{
		nb->strat.type = by_rr;
		nb->mov_to_sort = ft_bigger_nb(nb->strat.b_r, nb->strat.a_r);
	}
	else
	{
		nb->strat.type = by_rrr;
		nb->mov_to_sort = ft_bigger_nb(nb->strat.b_rr, nb->strat.a_rr);
	}
	if (nb->strat.b_rr + nb->strat.a_r < nb->strat.b_r + nb->strat.a_rr)
	{
		nb->strat.type = by_ra_rrb;
		nb->mov_to_sort = nb->strat.b_rr + nb->strat.a_rr;
	}
	else if (nb->strat.b_r + nb->strat.a_rr < nb->mov_to_sort)
	{
		nb->strat.type = by_ra_rrb;
		nb->mov_to_sort = nb->strat.b_rr + nb->strat.a_rr;
	}
}

t_nb	ft_best_to_sort(t_data *data)
{
	int		i;
	t_nb	*nb;
	t_nb	*best_nb;

	i = 0;
	best_nb = &data->s_b.stack[0];
	while (i < data->s_b.size)
	{
		nb = &data->s_b.stack[i];
		ft_mov_align_a(nb, &data->s_a, nb->sort_pos);
		ft_mov_to_top(nb, i, data->s_b.size);
		ft_set_mov_to_sort(nb);
		if (best_nb->mov_to_sort > nb->mov_to_sort)
			best_nb = nb;
		i++;
	}
	data->nb_sorted++;
	best_nb->is_sorted = true;
	DEBUG_CODE(
		printf("BEST NB TO SORT: %d\n", best_nb->nb);
		ft_print_strat(best_nb);
	)
	return (*best_nb);
}

void	ft_sort_nb(t_data *data, t_nb nb)
{
	int	i;

	if (nb.strat.type == by_rr)
	{
		i = ft_smaller_nb(nb.strat.b_r, nb.strat.a_r) + 1;
		while (--i != 0)
			ft_rotate_2(data);
		i = ft_abs_diff_nb(nb.strat.b_r, nb.strat.a_r) + 1;
		if (nb.strat.b_r > nb.strat.a_r)
			while (--i != 0)
				ft_rotate_b(data);
		else
			while (--i != 0)
				ft_rotate_a(data);
	}
	else if (nb.strat.type == by_rrr)
	{
		i = ft_smaller_nb(nb.strat.b_rr, nb.strat.a_rr) + 1;
		while (--i != 0)
			ft_reverse_rotate_2(data);
		i = ft_abs_diff_nb(nb.strat.b_rr, nb.strat.a_rr) + 1;
		if (nb.strat.b_rr > nb.strat.a_rr)
			while (--i != 0)
				ft_reverse_rotate_b(data);
		else
			while (--i != 0)
				ft_reverse_rotate_a(data);
	}
	else if (nb.strat.type == by_ra_rrb)
	{
		i = nb.strat.a_r + 1;
		while (--i != 0)
			ft_rotate_a(data);
		i = nb.strat.b_rr + 1;
		while (--i != 0)
			ft_reverse_rotate_b(data);
	}
	else if (nb.strat.type == by_rra_rb)
	{
		i = nb.strat.a_rr + 1;
		while (--i != 0)
			ft_reverse_rotate_a(data);
		i = nb.strat.b_r + 1;
		while (--i != 0)
			ft_rotate_b(data);
	}
	ft_push_a(data);
	if (nb.sort_pos > data->s_a.bigger_sort_pos)
		data->s_a.bigger_sort_pos = nb.sort_pos;
	if (nb.sort_pos < data->s_a.smaller_sort_pos)
		data->s_a.smaller_sort_pos = nb.sort_pos;
}

void	ft_sort_in_a(t_data *data)
{
	if (data->s_b.size == 0)
		return ;
	ft_sort_nb(data, ft_best_to_sort(data));
	DEBUG_CODE(
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		printf("Nb moves: %d\n", data->nb_moves);
	)
	ft_sort_in_a(data);
}

void	ft_rotate_sorted(t_data *data)
{
	int	curr_pos;

	curr_pos = -1;
	while (++curr_pos < data->s_a.size)
		if (data->s_a.stack[curr_pos].sort_pos == 0)
			break;
	if (curr_pos <= data->s_a.size / 2)
		while (curr_pos-- != 0)
			ft_reverse_rotate_a(data);
	else
	{
		curr_pos = data->s_a.size - curr_pos;
		while (curr_pos-- != 0)
			ft_rotate_a(data);
	}
}

void	ft_set_edge_sort_pos(t_stack *s)
{
	int	i;

	i = -1;
	s->smaller_sort_pos = s->size;
	s->bigger_sort_pos = -1;
	while (++i < s->size)
	{
		if (!s->stack[i].is_sorted)
			continue;
		if (s->smaller_sort_pos > s->stack[i].sort_pos)
			s->smaller_sort_pos = s->stack[i].sort_pos;
		if (s->bigger_sort_pos < s->stack[i].sort_pos)
			s->bigger_sort_pos = s->stack[i].sort_pos;
	}
}

void	ft_generate_ops(t_data *data)
{
	data->wait_to_swap = true;
	data->nb_moves = 0;
	DEBUG_CODE(printf("data->nb_sorted: %d\n", data->nb_sorted);)
	ft_set_edge_sort_pos(&data->s_a);
	ft_fill_b(data);
	DEBUG_CODE(
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		printf("Nb moves: %d\n", data->nb_moves);
	)
	ft_sort_in_a(data);
	ft_rotate_sorted(data);
	DEBUG_CODE(
		printf("\nFINAL RESULT:\n");
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		printf("Nb moves: %d\n", data->nb_moves);
	)
	ft_print_ops(data, op_none);
}