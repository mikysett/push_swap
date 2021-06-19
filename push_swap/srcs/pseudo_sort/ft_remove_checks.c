/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/18 15:19:42 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_remove_sgl_invalid(t_list **checks, t_stack *s);
static bool	ft_is_level_in_check(t_ps *ps, t_stack *s);

void	ft_remove_invalid_checks(t_list ***checks, t_stack *s)
{
	int		i;

	i = 0;
	while (i < s->size)
	{
		ft_remove_sgl_invalid(checks[i], s);
		i++;
	}
}

static void	ft_remove_sgl_invalid(t_list **checks, t_stack *s)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;
	t_ps	*curr_ps;

	prev = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (ft_is_level_in_check(curr_ps, s))
		{
			if (!prev)
				*checks = curr->next;
			else
				prev->next = curr->next;
			next = curr->next;
			ft_lstdelone(curr, ft_free_sgl_check);
			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

static bool	ft_is_level_in_check(t_ps *ps, t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->size)
	{
		if (ps->hash[i] == 1
			&& s->stack[i].is_sorted == s->sort_lvl)
			return (true);
		i++;
	}
	return (false);
}
