/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_in_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 02:00:02 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_sort_in_a(t_data *data)
{
	while (data->s_b.size > 0)
		ft_sort_nb(data, ft_best_to_sort(data));
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
		ft_set_nb_mov_to_top(nb, i, data->s_b.size);
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
