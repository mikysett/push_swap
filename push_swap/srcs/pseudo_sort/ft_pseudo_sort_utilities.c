/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/15 16:38:37 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_free_sgl_check(void *void_ps)
{
	t_ps *ps;

	ps = (t_ps *)void_ps;
	free(ps->hash);
	free(ps);
}

void	ft_free_checks(t_list ***checks, int s_size)
{
	int		i;

	i = 0;
	while (i < s_size)
	{
		ft_lstclear(checks[i], ft_free_sgl_check);
		free(checks[i]);
		i++;
	}
	free(checks);
}

void	ft_save_check(t_list **checks, t_ps *new)
{
	t_list	*new_el;

	new_el = ft_lstnew((void *)new);
	if (!new_el)
		ft_exit_failure();
	ft_lstadd_front(checks, new_el);
}

// void	ft_take_partial_best(t_ps **best, t_ps **new)
// {
// 	if ((*new) != 0
// 		&& ((*best) == 0 || (*best)->score < (*new)->score))
// 		(*best) = (*new);
// }

void	ft_set_is_sorted(t_stack *s, t_ps *ps)
{
	int	i;

	i = 0;
	while (i < s->size)
	{
		if (ps->hash[i] == true)
			s->stack[i].is_sorted = s->sorting_level;
		i++;
	}
}

int	ft_chunk_size(int stack_size, int pos, int first_pos)
{
	if (pos > first_pos)
		return (stack_size - pos + first_pos + 1);
	else
		return (first_pos - pos);
}

bool	ft_all_sorted_set(t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->size - 1)
	{
		if (!s->stack[i].is_sorted)
			return (false);
		i++;
	}
	return (true);
}
