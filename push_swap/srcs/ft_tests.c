/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:38:11 by msessa            #+#    #+#             */
/*   Updated: 2021/05/28 09:55:35 by msessa           ###   ########.fr       */
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
		{
			// printf("%s%4i. %20i|%20i|%20i|%s\n", CLR_RED,
			// i,
			// s->stack[i].nb,
			// s->stack[i].init_pos,
			// s->stack[i].sort_pos,
			// CLR_WHITE);
			sorted = false;
		}
		else
		{
			// printf("%4i. %20i|%20i|%20i|\n",
			// i,
			// s->stack[i].nb,
			// s->stack[i].init_pos,
			// s->stack[i].sort_pos);
		}
		i++;
	}
	if (sorted)
		printf("%sARRAY SORTED%s\n", CLR_GREEN, CLR_WHITE);
	else
		printf("%sARRAY NOT SORTED%s\n", CLR_RED, CLR_WHITE);
}

void	ft_print_stack(t_stack *s)
{
	int	i;
	int	nb_sorted;
	// int	nb_pseudo_lower;
	// int	nb_pseudo_higher;

	i = s->size - 1;
	nb_sorted = 0;
	// nb_pseudo_lower = 0;
	// nb_pseudo_higher = 0;
	printf("----  %20s|%20s|%20s|\n", "NUMBER", "INITIAL POS", "SORTED POS");
	while (i >= 0)
	{
		if (s->stack[i].is_sorted)
		{
			printf(CLR_GREEN);
			nb_sorted++;
		}
		// else if (s->stack[i].pseudo_sort_lower)
		// {
		// 	printf(CLR_YELLOW);
		// 	nb_pseudo_lower++;
		// }
		// else if (s->stack[i].pseudo_sort_higher)
		// {
		// 	printf(CLR_BLUE);
		// 	nb_pseudo_higher++;
		// }
		printf("%4i. %20i|%20i|%20i|\n", i,
			s->stack[i].nb,
			s->stack[i].init_pos,
			s->stack[i].sort_pos);
		printf(CLR_WHITE);
		i--;
	}

	// ft_set_sort_pos(s, 0, s->size - 1);
	// printf("\nSORTED ARRAY\n");
	// printf("\nAttention this changes the order of the elements in the stack!\n");
	// i = s->size - 1;
	// while (i >= 0)
	// {
	// 	if (s->stack[i].is_sorted)
	// 		printf(CLR_GREEN);
	// 	else if (s->stack[i].pseudo_sort_lower)
	// 		printf(CLR_YELLOW);
	// 	else if (s->stack[i].pseudo_sort_higher)
	// 		printf(CLR_BLUE);
	// 	printf("%4i. %20i|%20i|%20i|\n", i,
	// 		s->stack[i].nb,
	// 		s->stack[i].init_pos,
	// 		s->stack[i].sort_pos);
	// 	printf(CLR_WHITE);
	// 	i--;
	// }
	printf("%s%20s: %d%s\n", CLR_GREEN, "NB SORTED", nb_sorted, CLR_WHITE);
	// printf("%s%20s: %d%s\n", CLR_YELLOW, "NB PSEUDO LOWER", nb_pseudo_lower, CLR_WHITE);
	// printf("%s%20s: %d%s\n", CLR_BLUE, "NB PSEUDO HIGHER", nb_pseudo_higher, CLR_WHITE);
}

void	ft_print_pseudo_sorted(t_ps *pseudo_sorted)
{
	int	i;
	int	score = 0;

	i = 0;
	printf("Pseudo sorted hash (size: %d):\n", pseudo_sorted->size);
	while (i < pseudo_sorted->size)
	{
		if (pseudo_sorted->hash[i] == true)
		{
			score++;
			printf("1");
		}
		else
			printf("0");
		i++;
	}
	printf(" --- %sscore: %d%s\n", CLR_BLUE, score, CLR_WHITE);
}
