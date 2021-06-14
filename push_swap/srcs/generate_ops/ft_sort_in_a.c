/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_in_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 19:02:06 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_mov_align_a(t_nb *nb, t_stack *s, int nb_sort_pos)
{
	int	top;
	int	down;

	top = s->size;
	down = 0;
	nb->strat.a_r = 0;
	nb->strat.a_rr = 0;
	while (!ft_is_sort_pos(s, 1, nb_sort_pos, top))
	{
		nb->strat.a_r++;
		top--;
	}
	while (!ft_is_sort_pos(s, 1, nb_sort_pos, down))
	{
		nb->strat.a_rr++;
		down++;
	}
}

// static void	ft_mov_to_top(t_nb *nb, int nb_pos, int s_size)
// {
// 	nb->strat.b_r = s_size - 1 - nb_pos;
// 	nb->strat.b_rr = nb_pos + 1;
// }

static void	ft_set_mov_to_sort(t_nb *nb)
{
	if (ft_bigger(nb->strat.b_r, nb->strat.a_r)
		< ft_bigger(nb->strat.b_rr, nb->strat.a_rr))
	{
		nb->strat.type = by_rr;
		nb->mov_to_sort = ft_bigger(nb->strat.b_r, nb->strat.a_r);
	}
	else
	{
		nb->strat.type = by_rrr;
		nb->mov_to_sort = ft_bigger(nb->strat.b_rr, nb->strat.a_rr);
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

t_nb	*ft_best_to_sort(t_data *data, bool only_in_range)
{
	int		i;
	t_nb	*nb;
	t_nb	*best_nb;

	i = 0;
	best_nb = 0;
	while (i < data->s_b.size)
	{
		nb = &data->s_b.stack[i];
		if (!only_in_range || nb->in_range)
		{
			ft_mov_align_a(nb, &data->s_a, nb->sort_pos);
			// ft_mov_to_top(nb, i, data->s_b.size);
			nb->strat.b_r = data->s_b.size - 1 - i;
			nb->strat.b_rr = i + 1;
			ft_set_mov_to_sort(nb);
			if (!best_nb || best_nb->mov_to_sort > nb->mov_to_sort)
				best_nb = nb;
		}
		i++;
	}
	if (best_nb)
	{
		data->s_a.nb_sorted++;
		best_nb->is_sorted = 1;
		if (best_nb->in_range)
		{
			best_nb->in_range = false;
			data->s_b.nb_in_range--;
		}
		DEBUG_CODE(
			printf("BEST NB TO SORT: %d\n", best_nb->nb);
			ft_print_strat(best_nb);
		)
	}
	return (best_nb);
}

void	ft_sort_nb(t_data *data, t_nb *nb_ptr)
{
	int		i;
	t_nb	nb;

	if (!nb_ptr)
		return ;
	nb = *nb_ptr;
	if (nb.strat.type == by_rr)
	{
		i = ft_smaller(nb.strat.b_r, nb.strat.a_r) + 1;
		while (--i != 0)
			ft_rotate_2(data);
		i = ft_abs_diff(nb.strat.b_r, nb.strat.a_r) + 1;
		if (nb.strat.b_r > nb.strat.a_r)
			while (--i != 0)
				ft_rotate_b(data);
		else
			while (--i != 0)
				ft_rotate_a(data);
	}
	else if (nb.strat.type == by_rrr)
	{
		i = ft_smaller(nb.strat.b_rr, nb.strat.a_rr) + 1;
		while (--i != 0)
			ft_reverse_rotate_2(data);
		i = ft_abs_diff(nb.strat.b_rr, nb.strat.a_rr) + 1;
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

void	ft_sort_in_a(t_data *data, bool only_in_range)
{
	if (data->s_b.size == 0)
		return ;
	while (data->s_b.nb_in_range)
		ft_sort_nb(data, ft_best_to_sort(data, only_in_range));
	if (!only_in_range)
		ft_sort_nb(data, ft_best_to_sort(data, only_in_range));

	DEBUG_CODE(
		printf("ft sort in a, only_in_range: %d\n", only_in_range);
		printf("Stack A:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B:\n");
		ft_print_stack(&data->s_b);
		// printf("Nb moves: %d\n", data->nb_moves);
	)
}
