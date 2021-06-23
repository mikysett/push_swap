/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:38:11 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:18:58 by msessa           ###   ########.fr       */
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

void	ft_print_stack_ligh(t_data *data)
{
	int		i;
	char	colors[6][20] =
		{
			CLR_WHITE,
			CLR_RED,
			CLR_YELLOW,
			CLR_BLUE,
			CLR_PURPLE,
			CLR_CYAN
		};
	i = data->s_a.top > data->s_b.top ? data->s_a.top : data->s_b.top;
	printf("----  index. number .sorted_lvl\n");
	printf("%18s|%17s|\n", "  STACK A ", "  STACK B ");
	while (i >= 0)
	{
		if (i <= data->s_a.top)
		{
			if (data->s_a.stack[i].lis_lvl)
			{
				if (data->s_a.stack[i].lis_lvl >= 0)
					printf("%s", colors[(data->s_a.stack[i].lis_lvl + 1) % 6]);
			}
			else
			{
				printf("%s", colors[(data->s_a.stack[i].range + 1) % 6]);
			}
			printf("%s%4i.%s %5i%s .%5i|    ",
				CLR_GRAY,
				i,
				colors[(data->s_a.stack[i].lis_lvl + 1) % 6],
				data->s_a.stack[i].nb,
				CLR_GRAY,
				data->s_a.stack[i].lis_lvl);
			printf(CLR_WHITE);
		}
		else
			printf("%18s|    ", " ");
		if (i <= data->s_b.top)
		{
			if (data->s_b.stack[i].lis_lvl)
			{
				if (data->s_b.stack[i].lis_lvl >= 0)
					printf("%s", colors[(data->s_b.stack[i].lis_lvl + 1) % 6]);
			}
			else
			{
				printf("%s", colors[(data->s_b.stack[i].range + 1) % 6]);
			}
			printf("%s %5i%s .%5i|    ",
				colors[(data->s_b.stack[i].lis_lvl + 1) % 6],
				data->s_b.stack[i].nb,
				CLR_GRAY,
				data->s_b.stack[i].lis_lvl);
			printf(CLR_WHITE);
		}
		printf("\n");
		i--;
	}
	printf("-------------- SIZES ---------------|\n");
	printf("%18d|%17d|\n", data->s_a.top + 1, data->s_b.top + 1);
	printf("-------------- NB LEVELS -----------|\n");
	printf("%18d|%17d|\n", ft_count_lvl(&data->s_a), ft_count_lvl(&data->s_b));
	printf(CLR_WHITE);
}

void	ft_print_stack(t_stack *s)
{
	int		i;
	int		nb_sorted;
	char	colors[6][20] =
		{
			CLR_WHITE,
			CLR_RED,
			CLR_YELLOW,
			CLR_BLUE,
			CLR_PURPLE,
			CLR_CYAN
		};
	i = s->size - 1;
	nb_sorted = 0;
	printf("----  %20s|%20s|%20s|%20s|%20s|\n", "NUMBER", "INITIAL POS", "SORTED POS", "IS SORTED", "RANGE");
	while (i >= 0)
	{
		if (s->stack[i].in_range == true)
			printf(CLR_YELLOW);
		else if (s->stack[i].lis_lvl)
		{
			if (s->stack[i].lis_lvl >= 0)
				printf("%s", colors[(s->stack[i].lis_lvl + 1) % 6]);
			nb_sorted++;
		}
		else
		{
			printf("%s", colors[(s->stack[i].range + 1) % 6]);
		}
		printf("%4i. %20i|%20i|%20i|%20i|%20i|\n", i,
			s->stack[i].nb,
			s->stack[i].init_pos,
			s->stack[i].sort_pos,
			s->stack[i].lis_lvl,
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

void	ft_print_checks_nb(t_list ***checks, int s_a_size)
{
	int	i;

	i = 0;
	while (i < s_a_size)
	{
		printf("%3d. list size: %d\n", i, ft_lstsize(*checks[i]));
		i++;
	}
}

// void	ft_print_stats(t_data *data)
// {
// 	printf("----> DATA STATS\n");
// 	printf("%24s %7d\n", "fill_b:", data->stats.fill_b);
// 	printf("%24s %7d\n", "sort_not_in_range:", data->stats.sort_not_in_range);
// 	printf("%24s %7d\n", "reduce_not_in_range:", data->stats.reduce_not_in_range);
// 	printf("%24s %7d\n", "organize_not_in_range:", data->stats.organize_not_in_range);
// 	printf("%24s %7d\n", "merge_stacks:", data->stats.merge_stacks);
// 	printf("%24s %7d\n", "rotate_sorted:", data->stats.rotate_sorted);
// }