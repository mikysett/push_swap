/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/04 01:30:28 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_free_pseudo_sort(t_ps *pseudo_sort)
{
	free(pseudo_sort->hash);
	free(pseudo_sort);
}

void	ft_init_ps_rec(t_ps_rec *rec, t_stack *s, int pos)
{
	rec->best = 0;
	rec->new = 0;
	rec->pos_nb = s->stack[pos].nb;
	// rec->s_size = s->size;
}

void	ft_init_ps_data(t_ps_data *ps_data, t_stack *s)
{
	int	i;

	ps_data->s = s;
	ps_data->best = 0;
	ps_data->new = 0;
	ps_data->nb_rec = 0;
	ps_data->checks = ft_calloc(s->size, sizeof(t_list **));
	if (!ps_data->checks)
		ft_exit_failure();
	i = 0;
	while (i < s->size)
	{
		ps_data->checks[i] = ft_calloc(1, sizeof(t_list *));
		if (!ps_data->checks[i])
			ft_exit_failure();
		i++;
	}
}

t_list	***ft_init_checks(int s_size)
{
	t_list	***checks;
	int		i;

	checks = ft_calloc(s_size, sizeof(t_list **));
	if (!checks)
		ft_exit_failure();
	i = 0;
	while (i < s_size)
	{
		checks[i] = ft_calloc(1, sizeof(t_list *));
		if (!checks[i])
			ft_exit_failure();
		i++;
	}
	return (checks);
}

static int	ft_get_partial_score(t_ps *curr_ps, int size, int curr_pos, int initial_pos)
{
	int	partial_score;
	
	partial_score = 0;
	while (curr_pos != initial_pos)
	{
		if (curr_ps->hash[curr_pos] != 0)
			partial_score++;
		curr_pos++;
		if (curr_pos == size)
			curr_pos = 0;
	}
	return (partial_score);
}

t_ps	*ft_best_checked(t_list **checks, int s_size, int curr_pos, int initial_pos)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;
	int		curr_chunck_size;
	int		partial_score;
	int		best_partial_score;

	curr = *checks;
	best_partial_score = 0;
	best = 0;
	if (!curr)
		return (0);
	if (curr_pos > initial_pos)
		curr_chunck_size = s_size - curr_pos;
	else
		curr_chunck_size = initial_pos - curr_pos;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (curr_chunck_size <= curr_ps->chunk_size)
		{
			partial_score = ft_get_partial_score(curr_ps, s_size, curr_pos, initial_pos);
			if (partial_score > best_partial_score)
			{
				best = curr_ps;
				best->partial_score = partial_score;
				best_partial_score = partial_score;
			}
		// 	printf("%sSERVING FROM BUFFER CHECKS, SIZE: %d%s\n",
		// 		CLR_GREEN,
		// 		curr_ps->size,
		// 		CLR_WHITE);
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

