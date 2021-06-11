/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:38:11 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 18:03:33 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Only for tests in dev, not to be submitted

#include "ft_push_swap.h"

void	ft_is_sorted(t_stack *s)
{
	bool	sorted;
	int		i;

	sorted = true;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb > s->stack[i - 1].nb)
			sorted = false;
		i++;
	}
	if (sorted)
		printf("%sARRAY SORTED%s\n", CLR_GREEN, CLR_WHITE);
	else
		printf("%sARRAY NOT SORTED%s\n", CLR_RED, CLR_WHITE);
}

void	ft_print_stack(t_stack *s)
{
	int		i;
	int		nb_sorted;
	char	colors[7][20] =
		{
			CLR_WHITE,
			CLR_RED,
			CLR_GREEN,
			CLR_YELLOW,
			CLR_BLUE,
			CLR_PURPLE,
			CLR_CYAN
		};
	i = s->size - 1;
	nb_sorted = 0;
	printf("----  %20s|%20s|%20s|%20s|\n", "NUMBER", "INITIAL POS", "SORTED POS", "RANGE");
	while (i >= 0)
	{
		if (s->stack[i].in_range == true)
			printf(CLR_YELLOW);
		else if (s->stack[i].is_sorted > 0)
		{
			printf(CLR_GREEN);
			nb_sorted++;
		}
		else
		{
			printf("%s", colors[(s->stack[i].range + 1) % 7]);
		}
		printf("%4i. %20i|%20i|%20i|%20i|\n", i,
			s->stack[i].nb,
			s->stack[i].init_pos,
			s->stack[i].sort_pos,
			s->stack[i].range);
		printf(CLR_WHITE);
		i--;
	}
	printf("%s%20s: %d%s\n", CLR_GREEN, "NB SORTED", nb_sorted, CLR_WHITE);
}

void	ft_print_pseudo_sorted(t_ps *pseudo_sorted)
{
	int	i;
	int	score = 0;

	i = 0;
	while (i < pseudo_sorted->size)
	{
		if (pseudo_sorted->hash[i] != 0)
		{
			score++;
			printf("%d", pseudo_sorted->hash[i]);
		}
		else
			printf("0");
		i++;
	}
	printf(" --- %sscore: %d%s\n", CLR_BLUE, score, CLR_WHITE);
}

void	ft_print_checks(t_list ***checks, int size)
{
	t_list	*curr;
	t_ps	*curr_ps;
	int		i;
	int		nb_checks;

	i = 0;
	nb_checks = 0;
	while (i < size)
	{
		printf("%sChecks for: %d%s\n", CLR_YELLOW, i, CLR_WHITE);
		curr = *checks[i];
		while (curr)
		{
			curr_ps = (t_ps *)curr->content;
			ft_print_pseudo_sorted(curr_ps);
			curr = curr->next;
			nb_checks++;
		}
		i++;
	}
	printf("Total checks: %d\n", nb_checks);
}

void	ft_print_strat(t_nb *nb)
{
	printf("sorting strat for nb: %d\n", nb->nb);
	printf("%12s: %d\n", "mov_to_sort", nb->mov_to_sort);
	printf("%12s: %d\n", "b_r", nb->strat.b_r);
	printf("%12s: %d\n", "b_rr", nb->strat.b_rr);
	printf("%12s: %d\n", "a_r", nb->strat.a_r);
	printf("%12s: %d\n", "a_rr", nb->strat.a_rr);
	printf("%12s: %d\n", "type", nb->strat.type);
}

void	ft_print_data_range(t_data *data)
{
	printf("ind_start: %d  |  ind_end: %d  |  start_nb: %d  |  end_nb: %d\n",
		data->range.ind_start,
		data->range.ind_end,
		data->range.start_nb,
		data->range.end_nb);
}

void	ft_print_checks_nb(t_list ***checks, int s_a_size)
{
	int	i;
	int	nb_checks;

	i = 0;
	while (i < s_a_size)
	{
		printf("%3d. list size: %d\n", i, ft_lstsize(*checks[i]));
		i++;
	}
}

void	ft_print_ranges(t_data *data)
{
	int	i;

	i = 0;
	printf("---->   PRINT RANGES\n");
	while (i < data->nb_ranges)
	{
		printf("%7d. ind_start: %5d, ind_end: %5d,           start_nb: %5d, end_nb: %5d\n",
			i,
			data->ranges[i].ind_start,
			data->ranges[i].ind_end,
			data->ranges[i].start_nb,
			data->ranges[i].end_nb);
		i++;
	}
}

void	ft_print_stats(t_data *data)
{
	printf("----> DATA STATS\n");
	printf("%24s %7d\n", "fill_b:", data->stats.fill_b);
	printf("%24s %7d\n", "sort_not_in_range:", data->stats.sort_not_in_range);
	printf("%24s %7d\n", "reduce_not_in_range:", data->stats.reduce_not_in_range);
	printf("%24s %7d\n", "organize_not_in_range:", data->stats.organize_not_in_range);
	printf("%24s %7d\n", "merge_stacks:", data->stats.merge_stacks);
	printf("%24s %7d\n", "rotate_sorted:", data->stats.rotate_sorted);
}