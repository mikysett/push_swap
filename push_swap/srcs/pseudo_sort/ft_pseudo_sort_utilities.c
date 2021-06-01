/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/01 17:04:11 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_free_sgl_check(void *void_ps)
{
	t_ps *ps;

	ps = (t_ps *)void_ps;
	free(ps->hash);
	free(ps);
}

void	ft_free_checks(t_ps_data *ps_data)
{
	int		i;

	i = 0;
	while (i < ps_data->s->size)
	{
		ft_lstclear(ps_data->checks[i], ft_free_sgl_check);
		free(ps_data->checks[i]);
		i++;
	}
	free(ps_data->checks);
}

void	ft_save_check(t_list **checks, t_ps *new)
{
	t_list	*new_el;

	new_el = ft_lstnew((void *)new);
	if (!new_el)
		ft_exit_failure();
	ft_lstadd_front(checks, new_el);
}

void	ft_take_best(t_ps **best, t_ps **new)
{
	if ((*best) == 0 || (*best)->score < (*new)->score)
		(*best) = (*new);

	// if ((*best) == 0)
	// 	(*best) = (*new);
	// else if ((*best)->score < (*new)->score)
	// {
	// 	ft_free_pseudo_sort(*best);
	// 	(*best) = (*new);
	// }
	// else
	// 	ft_free_pseudo_sort(*new);
}

void	ft_set_is_sorted(t_stack *s, t_ps *ps)
{
	int	i;
	int	j;

	i = s->size - 1;
	j = ps->size - 1;
	while (j >= 0)
	{
		if (ps->hash[j] == true)
			s->stack[i].is_sorted = true;
		i--;
		j--;
	}
}


