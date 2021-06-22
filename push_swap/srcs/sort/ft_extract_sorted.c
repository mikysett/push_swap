/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_sorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 21:34:29 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_extract_first_level(t_data *data, int lis_lvl);
static int	ft_nb_sorted(t_stack *s, int lis_lvl);
static void	ft_extract_lis_lvl_from_stack(t_data *data,
	t_s_name in_name, int lis_lvl);

void	ft_extract_sorted(t_data *data)
{
	int	lis_lvl;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	lis_lvl = 1;
	ft_extract_first_level(data, lis_lvl);
	ft_rotate_sorted(data, stack_a);
	lis_lvl += 2;
	while (data->s_a.size_unsorted || data->s_b.size_unsorted)
	{
		if (data->s_a.size_unsorted)
			ft_extract_lis_lvl_from_stack(data, stack_a, lis_lvl);
		else
			ft_extract_lis_lvl_from_stack(data, stack_b, lis_lvl);
		lis_lvl += 2;
	}
}

static void	ft_extract_first_level(t_data *data, int lis_lvl)
{
	t_nb	*stack_a;

	stack_a = data->s_a.stack;
	while (!ft_only_one_level(&data->s_a))
	{
		ft_expand_lvl_by_swap(data, &data->s_a, lis_lvl);
		if (stack_a[data->s_a.top].lis_lvl == lis_lvl)
			ft_rotate_a(data);
		else if (stack_a[data->s_a.top].lis_lvl == lis_lvl + 1)
		{
			ft_push_b(data);
			ft_rotate_b(data);
		}
		else
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
		}
	}
}

bool	ft_expand_lvl_by_swap(t_data *data, t_stack *s, int lis_lvl)
{
	if (s->top <= 0)
		return (false);
	if (s->stack[s->top].lis_lvl == lis_lvl)
	{
		if(s->stack[s->top - 1].lis_lvl != lis_lvl
			&& ft_can_be_in_middle(s->stack[s->top - 1].nb,
				&s->stack[s->top], ft_next_in_lvl(s, s->top, lis_lvl)))
		{
			s->stack[s->top - 1].lis_lvl = lis_lvl;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[s->top - 1].lis_lvl == lis_lvl)
	{
		if	(ft_can_be_in_middle(s->stack[s->top].nb,
				&s->stack[s->top - 1], ft_next_in_lvl(s, s->top - 1, lis_lvl)))
		{
			s->stack[s->top].lis_lvl = lis_lvl;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[s->top].lis_lvl == lis_lvl + 1)
	{
		if (s->stack[s->top - 1].lis_lvl != lis_lvl + 1
			&& ft_can_be_in_middle(s->stack[s->top - 1].nb,
				&s->stack[s->top], ft_next_in_lvl(s, s->top, lis_lvl + 1)))
		{
			s->stack[s->top].lis_lvl = lis_lvl + 1;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[s->top - 1].lis_lvl == lis_lvl + 1)
	{
		if (ft_can_be_in_middle(s->stack[s->top].nb,
				&s->stack[s->top - 1], ft_next_in_lvl(s, s->top - 1, lis_lvl + 1)))
		{
			s->stack[s->top].lis_lvl = lis_lvl + 1;
			ft_swap_a(data);
			return (true);
		}
	}
	return (false);
}

static int	ft_nb_sorted(t_stack *s, int lis_lvl)
{
	int	i;
	int	nb_sorted;

	i = 0;
	nb_sorted = 0;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl == lis_lvl)
			nb_sorted++;
		i++;
	}
	return (nb_sorted);
}

static void	ft_extract_lis_lvl_from_stack(t_data *data,
	t_s_name from_name, int lis_lvl)
{
	t_merge_info	info;

	info.in_name = ft_opposite_s(from_name);
	ft_init_stacks_name(data, &info);
	while (info.s_from->size_unsorted > 0)
	{
		if (info.s_from->stack[info.s_from->top].lis_lvl == lis_lvl)
		{
			ft_rotate_stack(data, from_name);
			info.s_from->size_unsorted--;
		}
		else if (info.s_from->stack[info.s_from->top].lis_lvl == lis_lvl + 1)
		{
			ft_push_stack(data, ft_opposite_s(from_name));
			ft_rotate_stack(data, ft_opposite_s(from_name));
			info.s_from->size_unsorted--;
		}
		else if (lis_lvl % 4 == 1
			&& ft_expand_lvl_by_swap(data, info.s_from, lis_lvl))
			continue;
		else
		{
			ft_push_stack(data, ft_opposite_s(from_name));
			info.s_in->size_unsorted++;
			info.s_from->size_unsorted--;
		}
	}
}

void	ft_init_stacks_name(t_data *data, t_merge_info *m)
{
	if (m->in_name == stack_a)
	{
		m->s_in = &data->s_a;
		m->s_from = &data->s_b;
	}
	else
	{
		m->s_in = &data->s_b;
		m->s_from = &data->s_a;
	}
}