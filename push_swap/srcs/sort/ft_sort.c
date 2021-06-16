/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 01:13:51 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_sort(t_data *data)
{
	int	sorting_level;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	ft_extract_sorted(data);

	DEBUG_CODE(
		printf("ft_extract_first_level COMPLETED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B initial:\n");
		ft_print_stack(&data->s_b);
		// ft_print_ops(data, op_none);
	)

	ft_merge_sorted(data);
	// ft_reverse_b(data);

	DEBUG_CODE(
		printf("MERGING SORTED COMPLETED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
		printf("Stack B initial:\n");
		ft_print_stack(&data->s_b);
		ft_print_ops(data, op_none);
		ft_exit_failure();
	)

	ft_generate_ops(data);

	ft_rotate_sorted(data);
	ft_print_ops(data, op_none);
}

void	ft_extract_sorted(t_data *data)
{
	int	sorting_level;

	data->s_a.size_unsorted = 0;
	data->s_b.size_unsorted = 0;
	sorting_level = 2;
	ft_extract_first_level(data, sorting_level);
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



// bool	ft_stack_b_has_one_level(t_data *data)
// {
// 	int	i;
// 	int	level;

// 	i = 1;
// 	if (data->s_b.size <= 1)
// 	{
// 		printf("STACK B SMALLER THAN 2\n");
// 		return (true);
// 	}
// 	level = data->s_b.stack[0].is_sorted;
// 	while (i < data->s_b.size)
// 	{
// 		if (level != data->s_b.stack[i].is_sorted)
// 			return (false);
// 		i++;
// 	}
// 	printf("STACK B HAS ONLY ONE LEVEL\n");
// 	return (true);
// }

void	ft_merge_sorted(t_data *data)
{
	int				i = 0;
	int				curr_level;
	t_stack_type	merge_into;

	merge_into = stack_a;
	while (data->s_b.size)
	{
		if (merge_into == stack_a)
		{
			ft_merge_into_a(data);
			merge_into = stack_b;
		}
		else
		{
			ft_merge_into_b(data);
			merge_into = stack_a;
		}
		DEBUG_CODE(
			printf("MERGING LEVEL X\n");
			printf("Stack A:\n");
			ft_print_stack(&data->s_a);
			printf("Stack B:\n");
			ft_print_stack(&data->s_b);
		)

		// if (ft_stack_b_has_one_level(data))
		// 	break;

		i++;
		if (i == 8)
			break;
	}
}

void	ft_merge_into_a(t_data *data)
{
	int	level_to_sort;
	int	top_a;
	int	top_b;

	top_a = data->s_a.size - 1;
	top_b = data->s_b.size - 1;
	level_to_sort = data->s_b.stack[top_b].is_sorted;
	printf("MERGING INTO A LEVEL: %d\n", level_to_sort);
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
	printf("MERGING INTO B LEVEL: %d\n", level_to_sort);
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










































int	prev_p(int pos, int step, int stack_size)
{
	if (pos - step < 0)
		return (stack_size + (pos - step));
	else
		return (pos - step);
}

int	next_p(int pos, int step, int stack_size)
{
	if (pos + step > stack_size - 1)
		return (pos + step - stack_size);
	else
		return (pos + step);
}

static void	ft_rotate_sorted(t_data *data)
{
	int	curr_pos;

	curr_pos = -1;
	while (++curr_pos < data->s_a.size)
		if (data->s_a.stack[curr_pos].sort_pos == 0)
			break;
	if (curr_pos <= data->s_a.size / 2)
		while (curr_pos-- != 0)
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_reverse_rotate_a(data);
		}
	else
	{
		curr_pos = data->s_a.size - curr_pos;
		while (curr_pos-- != 0)
		{
			DEBUG_CODE(data->stats.rotate_sorted++;)
			ft_rotate_a(data);
		}
	}
}

static void	ft_set_edge_sort_pos(t_stack *s)
{
	int	i;

	i = -1;
	s->smaller_sort_pos = s->size;
	s->bigger_sort_pos = -1;
	while (++i < s->size)
	{
		if (!s->stack[i].is_sorted)
			continue;
		if (s->smaller_sort_pos > s->stack[i].sort_pos)
			s->smaller_sort_pos = s->stack[i].sort_pos;
		if (s->bigger_sort_pos < s->stack[i].sort_pos)
			s->bigger_sort_pos = s->stack[i].sort_pos;
	}
}
