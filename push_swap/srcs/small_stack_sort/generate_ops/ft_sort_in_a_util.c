/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_in_a_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 01:39:03 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_set_nb_mov_to_top(t_nb *nb, int nb_pos, int s_size)
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
