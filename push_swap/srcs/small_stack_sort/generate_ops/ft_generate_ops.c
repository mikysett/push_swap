/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 19:32:27 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_generate_ops(t_data *data)
{
	data->wait_to_swap = true;
	ft_set_edge_sort_pos(&data->s_a);
	ft_fill_b(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
	ft_sort_in_a(data);
	DEBUG_CODE(ft_print_stack_ligh(data);)
}

void	ft_set_edge_sort_pos(t_stack *s)
{
	int	i;

	i = -1;
	s->smaller_sp = s->size;
	s->bigger_sp = -1;
	while (++i < s->size)
	{
		if (!s->stack[i].lis_lvl)
			continue;
		if (s->smaller_sp > s->stack[i].sort_pos)
			s->smaller_sp = s->stack[i].sort_pos;
		if (s->bigger_sp < s->stack[i].sort_pos)
			s->bigger_sp = s->stack[i].sort_pos;
	}
}

void	ft_mov_align_a(t_nb *nb, t_stack *s, int nb_sort_pos)
{
	int	top;
	int	down;

	top = s->size - 1;
	down = 0;
	nb->strat.a_r = 0;
	nb->strat.a_rr = 1;
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


void	ft_sort_in_a(t_data *data)
{
	while (data->s_b.size > 0)
		ft_sort_nb(data, ft_best_to_sort(data));
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
	if (nb.sort_pos > data->s_a.bigger_sp)
		data->s_a.bigger_sp = nb.sort_pos;
	if (nb.sort_pos < data->s_a.smaller_sp)
		data->s_a.smaller_sp = nb.sort_pos;
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
	best_nb->lis_lvl = 1;
	DEBUG_CODE(
		printf("BEST NB TO SORT: %d\n", best_nb->nb);
		ft_print_strat(best_nb);
	)
	return (*best_nb);
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
