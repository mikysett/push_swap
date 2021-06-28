/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lvl_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/28 17:11:53 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_s_name	ft_choose_best_stack_to_merge(t_data *data)
{
	if (ft_get_lvl_size(&data->s_a, data->s_a.stack[data->s_a.top].lis_lvl)
		+ ft_get_lvl_size(&data->s_b, data->s_b.stack[data->s_b.top].lis_lvl)
		>= (data->s_a.size + data->s_b.size) / 2)
		return (stack_a);
	else
		return (ft_stack_with_less_lvl(data));
}

t_s_name	ft_stack_with_less_lvl(t_data *data)
{
	int	nb_lvl_a;
	int	nb_lvl_b;

	nb_lvl_a = ft_count_lvl(&data->s_a);
	nb_lvl_b = ft_count_lvl(&data->s_b);
	if (nb_lvl_a > nb_lvl_b)
		return (stack_b);
	return (stack_a);
}


bool	ft_top_lvl_reversed(t_stack *s, int pos)
{
	int	level;

	if (pos < 1)
		return (false);
	level = s->stack[pos].lis_lvl;
	if (s->stack[pos - 1].lis_lvl == level
		&& s->stack[pos - 1].nb < s->stack[pos].nb)
		return (true);
	return (false);
}

bool	ft_bottom_lvl_reversed(t_stack *s, int pos)
{
	int	level;

	if (s->size < 2)
		return (false);
	level = s->stack[pos].lis_lvl;
	if (s->stack[pos + 1].lis_lvl == level
		&& s->stack[pos + 1].nb > s->stack[pos].nb)
		return (true);
	return (false);
}

bool	ft_any_reversed_lvl_in_stack(t_stack *s)
{
	int	pos;

	pos = s->top;
	while (pos >= 0)
	{
		if (ft_top_lvl_reversed(s, pos))
			return (true);
		pos = ft_get_next_lvl_pos(s, pos);
	}
	return (false);
}
