/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_nb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 01:56:50 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_sort_nb_by_rr(t_data *data, t_nb nb);
static void	ft_sort_nb_by_rrr(t_data *data, t_nb nb);
static void	ft_sort_nb_by_ra_rrb(t_data *data, t_nb nb);
static void	ft_sort_nb_by_rra_rb(t_data *data, t_nb nb);

void	ft_sort_nb(t_data *data, t_nb nb)
{
	if (nb.strat.type == by_rr)
		ft_sort_nb_by_rr(data, nb);
	else if (nb.strat.type == by_rrr)
		ft_sort_nb_by_rrr(data, nb);
	else if (nb.strat.type == by_ra_rrb)
		ft_sort_nb_by_ra_rrb(data, nb);
	else if (nb.strat.type == by_rra_rb)
		ft_sort_nb_by_rra_rb(data, nb);
	ft_push_a(data);
	if (nb.sort_pos > data->s_a.bigger_sp)
		data->s_a.bigger_sp = nb.sort_pos;
	if (nb.sort_pos < data->s_a.smaller_sp)
		data->s_a.smaller_sp = nb.sort_pos;
}

static void	ft_sort_nb_by_rr(t_data *data, t_nb nb)
{		
	int	i;

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

static void	ft_sort_nb_by_rrr(t_data *data, t_nb nb)
{		
	int	i;

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

static void	ft_sort_nb_by_ra_rrb(t_data *data, t_nb nb)
{		
	int	i;

	i = nb.strat.a_r + 1;
	while (--i != 0)
		ft_rotate_a(data);
	i = nb.strat.b_rr + 1;
	while (--i != 0)
		ft_reverse_rotate_b(data);
}

static void	ft_sort_nb_by_rra_rb(t_data *data, t_nb nb)
{		
	int	i;

	i = nb.strat.a_rr + 1;
	while (--i != 0)
		ft_reverse_rotate_a(data);
	i = nb.strat.b_r + 1;
	while (--i != 0)
		ft_rotate_b(data);
}
