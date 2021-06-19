/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_sorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/18 15:55:39 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_extract_first_level(t_data *data, int sort_lvl);
static int	ft_nb_sorted(t_stack *s, int sort_lvl);
static void	ft_extract_sort_lvl_from_a(t_data *data, int sort_lvl);
static void	ft_extract_sort_lvl_from_b(t_data *data, int sort_lvl);

void	ft_extract_sorted(t_data *data)
{
	int	sort_lvl;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	sort_lvl = 1;
	ft_extract_first_level(data, sort_lvl);
	ft_rotate_sorted(data, &data->s_a, true);
	sort_lvl += 2;
	while (data->s_a.size_unsorted || data->s_b.size_unsorted)
	{
		if (data->s_a.size_unsorted)
			ft_extract_sort_lvl_from_a(data, sort_lvl);
		else
			ft_extract_sort_lvl_from_b(data, sort_lvl);
		sort_lvl += 2;
	}
}

static void	ft_extract_first_level(t_data *data, int sort_lvl)
{
	int		top;
	t_nb	*stack_a;

	stack_a = data->s_a.stack;
	while (!ft_only_one_level(&data->s_a))
	{
		top = data->s_a.size - 1;
		ft_increment_lvl_by_swap(data, &data->s_a, sort_lvl);
		if (stack_a[top].is_sorted == sort_lvl)
			ft_rotate_a(data);
		else if (stack_a[top].is_sorted == sort_lvl + 1)
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

bool	ft_increment_lvl_by_swap(t_data *data, t_stack *s, int sort_lvl)
{
	int	top;
	
	top = s->size - 1;
	if (top <= 0)
		return (false);
	if (s->stack[top].is_sorted == sort_lvl)
	{
		if(s->stack[top - 1].is_sorted != sort_lvl
			&& ft_can_be_in_middle(s->stack[top - 1].nb,
				&s->stack[top], ft_next_in_lvl(s, top, sort_lvl)))
		{
			s->stack[top - 1].is_sorted = sort_lvl;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[top - 1].is_sorted == sort_lvl)
	{
		if	(ft_can_be_in_middle(s->stack[top].nb,
				&s->stack[top - 1], ft_next_in_lvl(s, top - 1, sort_lvl)))
		{
			s->stack[top].is_sorted = sort_lvl;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[top].is_sorted == sort_lvl + 1)
	{
		if (s->stack[top - 1].is_sorted != sort_lvl + 1
			&& ft_can_be_in_middle(s->stack[top - 1].nb,
				&s->stack[top], ft_next_in_lvl(s, top, sort_lvl + 1)))
		{
			s->stack[top].is_sorted = sort_lvl + 1;
			ft_swap_a(data);
			return (true);
		}
	}
	else if (s->stack[top - 1].is_sorted == sort_lvl + 1)
	{
		if (ft_can_be_in_middle(s->stack[top].nb,
				&s->stack[top - 1], ft_next_in_lvl(s, top - 1, sort_lvl + 1)))
		{
			s->stack[top].is_sorted = sort_lvl + 1;
			ft_swap_a(data);
			return (true);
		}
	}
	return (false);
}

static int	ft_nb_sorted(t_stack *s, int sort_lvl)
{
	int	i;
	int	nb_sorted;

	i = 0;
	nb_sorted = 0;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted == sort_lvl)
			nb_sorted++;
		i++;
	}
	return (nb_sorted);
}

static void	ft_extract_sort_lvl_from_a(t_data *data, int sort_lvl)
{
	int		top;
	t_nb	*stack_a;

	stack_a = data->s_a.stack;
	while (data->s_a.size_unsorted > 0)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].is_sorted == sort_lvl)
		{
			ft_rotate_a(data);
			data->s_a.size_unsorted--;
		}
		else if (data->s_a.stack[top].is_sorted == sort_lvl + 1)
		{
			ft_push_b(data);
			ft_rotate_b(data);
			data->s_a.size_unsorted--;
		}
		else if (top > 0
			&& stack_a[top - 1].is_sorted == sort_lvl
			&& ft_can_be_in_middle(stack_a[top].nb,
				&stack_a[top - 1],
				ft_next_in_lvl(&data->s_a, top - 1, sort_lvl)))
		{
			DEBUG_CODE(printf("lvl size incremented!4\n");)
			stack_a[top].is_sorted = sort_lvl;
			ft_swap_a(data);
		}
		else if (top > 0
			&& stack_a[top - 1].is_sorted == sort_lvl + 1
			&& ft_can_be_in_middle(stack_a[top].nb,
				&stack_a[top - 1],
				ft_next_in_lvl(&data->s_a, top - 1, sort_lvl + 1)))
		{
			DEBUG_CODE(printf("lvl size incremented!5\n");)
			stack_a[top].is_sorted = sort_lvl + 1;
			ft_swap_a(data);
		}
		else
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
			data->s_a.size_unsorted--;
		}
	}
}

static void	ft_extract_sort_lvl_from_b(t_data *data, int sort_lvl)
{
	int	top;

	while (data->s_b.size_unsorted)
	{
		top = data->s_b.size - 1;
		if (data->s_b.stack[top].is_sorted == sort_lvl)
		{
			ft_rotate_b(data);
		}
		else if (data->s_b.stack[top].is_sorted == sort_lvl + 1)
		{
			ft_push_a(data);
			ft_rotate_a(data);
		}
		else
		{
			ft_push_a(data);
			data->s_a.size_unsorted++;
		}
		data->s_b.size_unsorted--;
	}
}