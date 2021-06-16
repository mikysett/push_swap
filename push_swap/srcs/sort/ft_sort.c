/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:29:17 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	ft_get_smallest_sort_pos(t_stack *s);

void	ft_sort(t_data *data)
{
	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	ft_extract_sorted(data);

	DEBUG_CODE(
		printf("EXTRACT SORTED COMPLETED\n");
		ft_print_stack_ligh(data);
		// ft_print_ops(data, op_none);
		// ft_exit_failure();
	)

	ft_merge_sorted(data);
	// ft_reverse_b(data);

	DEBUG_CODE(
		printf("FINAL STATUS OF BOTH STACKS:\n");
		ft_print_stack_ligh(data);
		ft_print_ops(data, op_none);
		ft_exit_failure();
	)

	// ft_generate_ops(data);

	ft_rotate_sorted(data, &data->s_a, true);
	ft_print_ops(data, op_none);
}

void	ft_extract_sorted(t_data *data)
{
	int	sorting_level;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	sorting_level = 2;
	ft_extract_first_level(data, sorting_level);
	ft_rotate_sorted(data, &data->s_a, true);
	sorting_level++;
	while (data->s_a.size_unsorted || data->s_b.size_unsorted)
	{
		if (data->s_a.size_unsorted)
			ft_extract_sorting_level_from_a(data, sorting_level);
		else
			ft_extract_sorting_level_from_b(data, sorting_level);
		sorting_level += 2;
	}
}

void	ft_extract_first_level(t_data *data, int sorting_level)
{
	int	top;
	int	b_size;

	b_size = data->s_a.size - ft_nb_sorted(&data->s_a, sorting_level - 1);
	while (data->s_b.size != b_size)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].is_sorted == sorting_level)
		{
			ft_push_b(data);
			ft_rotate_b(data);
		}
		else if (data->s_a.stack[top].is_sorted != 1)
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
		}
		else
			ft_rotate_a(data);
	}
}

int		ft_nb_sorted(t_stack *s, int sorting_level)
{
	int	i;
	int	nb_sorted;

	i = 0;
	nb_sorted = 0;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted == sorting_level)
			nb_sorted++;
		i++;
	}
	return (nb_sorted);
}

void	ft_extract_sorting_level_from_a(t_data *data, int sorting_level)
{
	int	top;

	while (data->s_a.size_unsorted)
	{
		top = data->s_a.size - 1;
		if (data->s_a.stack[top].is_sorted == sorting_level)
		{
			ft_rotate_a(data);
		}
		else if (data->s_a.stack[top].is_sorted == sorting_level + 1)
		{
			ft_push_b(data);
			ft_rotate_b(data);
		}
		else
		{
			ft_push_b(data);
			data->s_b.size_unsorted++;
		}
		data->s_a.size_unsorted--;
	}
}

void	ft_extract_sorting_level_from_b(t_data *data, int sorting_level)
{
	int	top;

	while (data->s_b.size_unsorted)
	{
		top = data->s_b.size - 1;
		if (data->s_b.stack[top].is_sorted == sorting_level)
		{
			ft_rotate_b(data);
		}
		else if (data->s_b.stack[top].is_sorted == sorting_level + 1)
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

void	ft_merge_sorted(t_data *data)
{
	bool	merge_into_a;

	merge_into_a = true;
	while (data->s_b.size)
	{
		if (ft_more_levels_in_a(data))
			merge_into_a = false;
		else
			merge_into_a = true;
		if (merge_into_a)
		{
			DEBUG_CODE(printf("MERGING B INTO A\n");)
			if (ft_level_reversed(&data->s_b))
				ft_invert_level(data, merge_into_a, &data->s_b);
			else if (ft_level_reversed(&data->s_a))
			{
				ft_invert_level(data, !merge_into_a, &data->s_b);
				continue;
			}
			ft_merge_into(data, merge_into_a, &data->s_a, &data->s_b);
		}
		else
		{
			DEBUG_CODE(printf("MERGING A INTO B\n");)
			if (ft_level_reversed(&data->s_a))
				ft_invert_level(data, merge_into_a, &data->s_a);
			else if (ft_level_reversed(&data->s_b))
			{
				ft_invert_level(data, !merge_into_a, &data->s_b);
				continue;
			}
			ft_merge_into(data, merge_into_a, &data->s_b, &data->s_a);
		}
		DEBUG_CODE(
			ft_print_stack_ligh(data);
		)
	}
}

bool	ft_more_levels_in_a(t_data *data)
{
	int	nb_lvl_a;
	int	nb_lvl_b;

	nb_lvl_a = ft_count_lvl(&data->s_a);
	nb_lvl_b = ft_count_lvl(&data->s_b);
	if (nb_lvl_a > nb_lvl_b)
		return (true);
	return (false);
}

int	ft_count_lvl(t_stack *s)
{
	int	i;
	int	nb_levels;
	int	curr_level;

	if (!s->size)
		return (0);
	i = 1;
	nb_levels = 1;
	curr_level = s->stack[0].is_sorted;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted != curr_level)
		{
			nb_levels++;
			curr_level = s->stack[i].is_sorted;
		}
		i++;
	}
	return (nb_levels);
}

bool	ft_level_reversed(t_stack *s)
{
	int	top;
	int	level;

	top = s->size - 1;
	if (top < 1)
		return (false);
	level = s->stack[top].is_sorted;
	if (s->stack[top - 1].is_sorted == level
		&& s->stack[top - 1].nb < s->stack[top].nb)
		return (true);
	return (false);
}

void	ft_invert_level(t_data *data, bool merge_into_a, t_stack *s)
{
	int	top;
	int	level;

	top = s->size - 1;
	if (top < 1)
		return ;
	level = s->stack[top].is_sorted;
	while (s->stack[top].is_sorted == level)
	{
		ft_push_stack(data, merge_into_a);
		top = s->size - 1;
	}
}

void	ft_merge_into(t_data *data, bool merge_into_a,
	t_stack *s_in, t_stack *s_from)
{
	int	level_to_sort;
	int	dest_level;
	int	top_in;
	int	top_from;

	top_in = s_in->size - 1;
	top_from = s_from->size - 1;
	level_to_sort = s_from->stack[top_from].is_sorted;
	dest_level = s_in->stack[top_in].is_sorted;
	DEBUG_CODE(printf("MERGING LEVEL: %d\n", level_to_sort);)
	while (s_from->stack[top_from].is_sorted == level_to_sort)
	{
		if (ft_only_one_level(s_in)
			&& s_from->stack[top_from].nb > ft_get_biggest_nb(s_in))
		{
			ft_rotate_sorted(data, s_in, merge_into_a);
			while (s_from->stack[top_from].is_sorted == level_to_sort)
			{
				s_from->stack[top_from].is_sorted = dest_level;
				ft_push_stack(data, merge_into_a);
				ft_rotate_stack(data, merge_into_a);
				top_from = s_from->size - 1;
				if (top_from == -1)
					break ;
			}
		}
		else if (s_from->stack[top_from].nb < s_in->stack[top_in].nb
			|| s_in->stack[top_in].is_sorted != dest_level)
		{
			s_from->stack[top_from].is_sorted = dest_level;
			ft_push_stack(data, merge_into_a);
		}
		else
			ft_rotate_stack(data, merge_into_a);
		top_in = s_in->size - 1;
		top_from = s_from->size - 1;
		if (top_from == -1)
			break;
	}
	top_in = s_in->size - 1;

	if (!ft_only_one_level(s_in))
		while (s_in->stack[top_in].is_sorted == dest_level)
			ft_rotate_stack(data, merge_into_a);
	else
		ft_rotate_sorted(data, s_in, merge_into_a);
}

bool	ft_only_one_level(t_stack *s)
{
	int	i;
	int	first_level;

	i = 1;
	if (s->size < 2)
		return (true);
	first_level = s->stack[0].is_sorted;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted != first_level)
			return (false);
		i++;
	}
	return (true);
}

void	ft_merge_into_a(t_data *data)
{
	int	level_to_sort;
	int	top_a;
	int	top_b;

	top_a = data->s_a.size - 1;
	top_b = data->s_b.size - 1;
	level_to_sort = data->s_b.stack[top_b].is_sorted;
	while (data->s_b.stack[top_b].is_sorted == level_to_sort)
	{
		if (data->s_b.stack[top_b].nb < data->s_a.stack[top_a].nb
			|| data->s_a.stack[top_a].is_sorted != level_to_sort - 1)
		{
			data->s_b.stack[top_b].is_sorted = level_to_sort - 1;
			ft_push_a(data);
		}
		else
			ft_rotate_a(data);
		top_a = data->s_a.size - 1;
		top_b = data->s_b.size - 1;
	}
	top_a = data->s_a.size - 1;
	while (data->s_a.stack[top_a].is_sorted == level_to_sort - 1)
		ft_rotate_a(data);
}

void	ft_merge_into_b(t_data *data)
{
	int	level_to_sort;
	int	top_a;
	int	top_b;

	top_a = data->s_a.size - 1;
	top_b = data->s_b.size - 1;
	level_to_sort = data->s_a.stack[top_a].is_sorted;
	while (data->s_a.stack[top_a].is_sorted == level_to_sort)
	{
		top_a = data->s_a.size - 1;
		top_b = data->s_b.size - 1;
		if (data->s_a.stack[top_a].nb > data->s_b.stack[top_b].nb
			|| data->s_b.stack[top_b].is_sorted != level_to_sort - 1)
		{
			data->s_a.stack[top_a].is_sorted = level_to_sort - 1;
			ft_push_b(data);
		}
		else
			ft_rotate_b(data);
		top_a = data->s_a.size - 1;
		top_b = data->s_b.size - 1;
	}
	top_b = data->s_b.size - 1;
	while (data->s_b.stack[top_b].is_sorted == level_to_sort - 1)
		ft_rotate_b(data);
}

void	ft_reverse_b(t_data *data)
{
	int	b_size = data->s_b.size;
	int	i;

	i = -1;
	while (++i < b_size)
		ft_push_a(data);
	i = -1;
	while (++i < b_size)
	{
		ft_push_b(data);
		ft_rotate_b(data);
	}
}

void	ft_rotate_sorted(t_data *data, t_stack *s, bool is_stack_a)
{
	int	curr_pos;
	int	smallest_sort_pos;

	curr_pos = -1;
	smallest_sort_pos = ft_get_smallest_sort_pos(s);
	while (++curr_pos < s->size)
		if (s->stack[curr_pos].sort_pos == smallest_sort_pos)
			break;
	if (curr_pos <= s->size / 2)
		while (curr_pos-- != 0)
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_reverse_rotate_stack(data, is_stack_a);
		}
	else
	{
		curr_pos = s->size - curr_pos;
		while (curr_pos-- != 0)
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_rotate_stack(data, is_stack_a);
		}
	}
}

static int	ft_get_smallest_sort_pos(t_stack *s)
{
	int	smallest_sort_pos;
	int	i;

	if (!s->size)
		return (0);
	smallest_sort_pos = s->stack[0].sort_pos;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].sort_pos < smallest_sort_pos)
			smallest_sort_pos = s->stack[i].sort_pos;
		i++;
	}
	return (smallest_sort_pos);
}

int			ft_get_biggest_nb(t_stack *s)
{
	int	biggest_nb;
	int	i;

	if (!s->size)
		return (0);
	biggest_nb = s->stack[0].nb;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb > biggest_nb)
			biggest_nb = s->stack[i].nb;
		i++;
	}
	return (biggest_nb);
}
