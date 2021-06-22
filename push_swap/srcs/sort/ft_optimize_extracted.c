/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimize_extracted.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 14:12:51 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_optimize_extracted_stack(t_stack *s);

void	ft_optimize_extracted(t_data *data)
{
	if (data->s_a.size > 1)
		ft_optimize_extracted_stack(&data->s_a);
	if (data->s_b.size > 1)
		ft_optimize_extracted_stack(&data->s_b);
}

static void	ft_optimize_extracted_stack(t_stack *s)
{
	int		curr_lvl;
	bool	curr_lvl_reversed;
	int		pos;

	pos = s->size - 1;
	while (pos >= 0)
	{
		curr_lvl = s->stack[pos].lis_lvl;
		curr_lvl_reversed = ft_top_level_reversed(s, pos);
		if (!curr_lvl_reversed && pos < s->size - 1
			&& s->stack[pos + 1].nb < s->stack[pos].nb)
			s->stack[pos + 1].lis_lvl = curr_lvl;
		pos = ft_get_next_lvl_pos(s, pos);
		if (pos == -1)
			return ;
		if (!curr_lvl_reversed
			&& s->stack[pos].nb > s->stack[pos + 1].nb)
			s->stack[pos].lis_lvl = curr_lvl;
	}
}

int	ft_get_next_lvl_pos(t_stack *s, int pos)
{
	int	curr_lvl;

	curr_lvl = s->stack[pos].lis_lvl;
	pos--;
	while (pos >= 0)
	{
		if (s->stack[pos].lis_lvl != curr_lvl)
			return (pos);
		pos--;
	}
	return (-1);
}