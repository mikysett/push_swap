/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_b_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:40:22 by msessa            #+#    #+#             */
/*   Updated: 2021/06/25 13:29:37 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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

void	ft_update_edge_sort_pos(t_stack *s, int nb_index)
{
	if (s->stack[nb_index].sort_pos > s->bigger_sp)
		s->bigger_sp = s->stack[nb_index].sort_pos;
	else if (s->stack[nb_index].sort_pos < s->smaller_sp)
		s->smaller_sp = s->stack[nb_index].sort_pos;
}

bool	ft_is_rotate_better(t_data *data)
{
	int	i;
	int	op_by_rotate;
	int	op_by_reverse;

	op_by_rotate = 0;
	i = 0;
	while (data->s_a.stack[i].lis_lvl)
		i++;
	op_by_reverse = i + 1;
	i = data->s_a.top;
	while (i != op_by_reverse - 1)
	{
		if (data->s_a.stack[i].lis_lvl)
			op_by_rotate++;
		else
			op_by_rotate = 0;
		i--;
	}
	if (op_by_rotate < op_by_reverse)
		return (true);
	return (false);
}

bool	ft_is_sort_pos(t_stack *s, int step, int nb_sort_pos, int pos)
{
	int	next_p_i;

	next_p_i = next_p(pos, step, s->size);
	if ((nb_sort_pos > s->stack[pos].sort_pos
		&& nb_sort_pos < s->stack[next_p_i].sort_pos)
		|| (nb_sort_pos > s->bigger_sp
			&& s->stack[pos].sort_pos == s->bigger_sp)
		|| (nb_sort_pos < s->smaller_sp
			&& s->stack[next_p_i].sort_pos == s->smaller_sp))
		return (true);
	return (false);
}

bool	ft_possible_sort_by_top(t_stack *s, int nb_sort_pos,
	int start, bool recursive)
{
	if (start < 0)
		return (false);
	if (s->stack[start].lis_lvl == 1)
	{
		if (s->stack[start].sort_pos == s->smaller_sp
			&& (nb_sort_pos > s->bigger_sp || nb_sort_pos < s->smaller_sp))
			return (true);
		else if (recursive)
			return (ft_possible_sort_by_top(s, s->stack[start].sort_pos,
					start - 1, true));
		else
			return (false);
	}
	else if (recursive)
		return (ft_possible_sort_by_top(s, s->stack[start].sort_pos,
				start - 1, true));
	else
		return (false);
}
