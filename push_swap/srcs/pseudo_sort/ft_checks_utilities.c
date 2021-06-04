/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:22:53 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 16:43:16 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_take_best(t_ps **best, t_ps **new)
{
	if ((*best) == 0 || (*best)->score < (*new)->score)
		(*best) = (*new);
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

t_ps	*ft_best_checked(t_list **checks, int s_size, int pos, int first_pos)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;
	int		curr_chunck_size;

	curr = *checks;
	if (!curr)
		return (0);
	best = 0;
	curr_chunck_size = ft_chunk_size(s_size, pos, first_pos);
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (curr_chunck_size <= curr_ps->chunk_size)
		{
			curr_ps->score = ft_get_partial_score(curr_ps, s_size,
				pos, first_pos);
			if (!best || curr_ps->score > best->score)
				best = curr_ps;
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
