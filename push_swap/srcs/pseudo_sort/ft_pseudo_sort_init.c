/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:08:23 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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

void	ft_init_ps_rec(t_ps_rec *rec, t_stack *s, int pos)
{
	rec->best = 0;
	rec->new = 0;
	rec->pos_nb = s->stack[pos].nb;
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
