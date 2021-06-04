/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 13:45:14 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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

/* Return the position of the larger sorted range in the stack */
// void	ft_get_larger_range(t_nb *s, int ssize, t_range *range)
// {
// 	int		i;
// 	int		j;
// 	int		range_size;

// 	i = 0;
// 	while (i < ssize)
// 	{
// 		j = i;
// 		range_size = 1;
// 		while (s[j].sort_pos == (s[next_p(j, 1, ssize)].sort_pos - 1) % ssize)
// 		{
// 			j = next_p(j, 1, ssize);
// 			if (j == i)
// 				break ;
// 			range_size++;
// 		}
// 		if (range_size > range->size)
// 		{
// 			range->size = range_size;
// 			range->lower = i;
// 		}
// 		i += range_size;
// 		// printf("biggest range: %d\n", range->size);
// 	}
// 	range->higher = next_p(range->lower, range->size - 1, ssize);
// }

// void	ft_set_sort_range(t_stack *s, t_range range)
// {
// 	int	i;
// 	int	curr;

// 	i = 0;
// 	curr = range.lower;
// 	while (i < range.size)
// 	{
// 		s->stack[curr].is_sorted = 1;
// 		curr = next_p(curr, 1, s->size);
// 		i++;
// 	}
// }

// void	ft_set_pseudo_sorted(t_stack *s, t_range *range)
// {
// 	int i;
// 	int	last_sort_nb;

// 	i = prev_p(range->lower, 1, s->size);
// 	last_sort_nb = s->stack[range->lower].nb;
// 	while (i != range->higher)
// 	{
// 		if (s->stack[i].nb > last_sort_nb)
// 		{
// 			s->stack[i].pseudo_sort_lower = true;
// 			last_sort_nb = s->stack[i].nb;
// 		}
// 		i = prev_p(i, 1, s->size);
// 	}

// 	i = next_p(range->higher, 1, s->size);
// 	last_sort_nb = s->stack[range->higher].nb;
// 	while (i != range->higher)
// 	{
// 		if (s->stack[i].nb < last_sort_nb)
// 		{
// 			s->stack[i].pseudo_sort_higher = true;
// 			last_sort_nb = s->stack[i].nb;
// 		}
// 		i = next_p(i, 1, s->size);
// 	}
// }

bool	ft_sort(t_data *data)
{
	// t_range	biggest_range;

	ft_set_pos(&data->s_a, true);
	// ft_set_sort_pos(&data->s_a_sorted, 0, data->s_a_sorted.size - 1);
	// if (ft_duplicated_nb(&data->s_a_sorted))
	// 	return (false);
	ft_set_sort_pos(&data->s_a, 0, data->s_a.size - 1);
	if (ft_duplicated_nb(&data->s_a))
		return (false);
	// if (ft_already_sorted(&data->s_a))
	// 	return (true);
	DEBUG_CODE(ft_is_sorted(&data->s_a);)
	// To remove if s_a_sorted is implemented
	ft_fix_pos(&data->s_a);

	// FALLBACK IF PSEUDO_SORT IS TOO SLOW?!
	// biggest_range.size = 0;
	// ft_get_larger_range(data->s_a.stack, data->s_a.size, &biggest_range);
	// ft_set_sort_range(&data->s_a, biggest_range);
	// ft_set_pseudo_sorted(&data->s_a, &biggest_range);
	
	ft_pseudo_sort(&data->s_a);
	// To test
	DEBUG_CODE(
		printf("PSEUDO SORTING CHECKS COMPLETED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data->s_a);
	)

	// while (1)
	// {
	// 	;
	// }
	ft_generate_ops(data);

	return (true);
}
