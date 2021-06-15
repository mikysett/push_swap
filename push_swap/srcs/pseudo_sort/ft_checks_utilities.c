/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:22:53 by msessa            #+#    #+#             */
/*   Updated: 2021/06/15 18:26:49 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_take_best(t_ps **best, t_ps **new)
{
	if (!*best || (*new && (*best)->score < (*new)->score))
	{
		if (*best)
			(*best)->protection_lvl--;
		(*new)->protection_lvl++;
		*best = *new;
	}
}

static int	ft_get_partial_score(t_ps *curr_ps, int size,
	int curr_pos, int first_pos)
{
	int	partial_score;
	
	partial_score = 0;
	while (curr_pos != first_pos)
	{
		if (curr_ps->hash[curr_pos] != 0)
			partial_score++;
		curr_pos++;
		if (curr_pos == size)
			curr_pos = 0;
	}
	return (partial_score);
}

void	ft_reduce_checked(t_list **checks)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;
	t_ps	*curr_ps;
	int		biggest_chunk_size;

	biggest_chunk_size = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (curr_ps->chunk_size > biggest_chunk_size)
			biggest_chunk_size = curr_ps->chunk_size;
		curr = curr->next;
	}
	prev = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (curr_ps->protection_lvl <= 0
			&& curr_ps->chunk_size < biggest_chunk_size)
		{
			if (!prev)
				*checks = curr->next;
			else
				prev->next = curr->next;
			next = curr->next;
			ft_lstdelone(curr, ft_free_sgl_check);
			curr = next;
			// printf("ONE BUFFER CLEANED ---<<<<<<------------\n");
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

t_ps	*ft_best_checked(t_list **checks, int s_size, int pos, int first_pos)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;
	int		curr_chunck_size;

	ft_reduce_checked(checks);
	curr = *checks;
	if (!curr)
		return (0);
	best = 0;
	curr_chunck_size = ft_chunk_size(s_size, pos, first_pos);
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		// printf("curr_chunk_size: %d  |  curr_ps->chunk_size: %d\n",
		// 	curr_chunck_size,
		// 	curr_ps->chunk_size);
		if (curr_chunck_size <= curr_ps->chunk_size)
		{
			curr_ps->score = ft_get_partial_score(curr_ps, s_size,
				pos, first_pos);
			// if (best)
			// 	printf("---------------> curr score: %d  |  best score: %d\n",
			// 		curr_ps->score,
			// 		best->score);
			if (!best || curr_ps->score > best->score)
			{
				// printf("%sTAKEN FROM BUFFER%s\n",
				// 	CLR_GREEN, CLR_WHITE);
				best = curr_ps;
			}
		}
		curr = curr->next;
	}
	return (best);
}

t_ps	*ft_abs_best_checked(t_list **checks)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;

	best = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (best == 0 || best->score < curr_ps->score)
			best = curr_ps;
		curr = curr->next;
	}
	return (best);
}
