/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lvl_counts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/23 15:36:37 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int		ft_count_lvl(t_stack *s)
{
	int	i;
	int	nb_levels;
	int	curr_level;

	if (!s->size)
		return (0);
	i = 1;
	nb_levels = 1;
	curr_level = s->stack[0].lis_lvl;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl != curr_level)
		{
			nb_levels++;
			curr_level = s->stack[i].lis_lvl;
		}
		i++;
	}
	return (nb_levels);
}

bool	ft_only_one_lvl(t_stack *s)
{
	int	i;
	int	first_level;

	i = 1;
	if (s->size < 2)
		return (true);
	first_level = s->stack[0].lis_lvl;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl != first_level)
			return (false);
		i++;
	}
	return (true);
}

int		ft_get_lvl_size(t_stack *s, int lis_lvl)
{
	int	i;
	int	lvl_size;

	i = 0;
	lvl_size = 0;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl == lis_lvl)
			lvl_size++;
		i++;
	}
	return (lvl_size);
}
