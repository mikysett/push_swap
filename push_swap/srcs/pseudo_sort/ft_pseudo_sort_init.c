/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/03 12:32:58 by msessa           ###   ########.fr       */
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
	rec->s_size = s->size;
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

t_ps	*ft_best_checked(t_list **checks)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;

	curr = *checks;
	if (curr)
	{
		best = (t_ps *)curr->content;
		curr = curr->next;
	}
	else
		return (0);
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (best->score < curr_ps->score)
		{
		// 	printf("%sSERVING FROM BUFFER CHECKS, SIZE: %d%s\n",
		// 		CLR_GREEN,
		// 		curr_ps->size,
		// 		CLR_WHITE);
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

