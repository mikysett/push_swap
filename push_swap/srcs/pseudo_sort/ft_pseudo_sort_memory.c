/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:06:36 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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

void	ft_free_sgl_check(void *void_ps)
{
	t_ps *ps;

	ps = (t_ps *)void_ps;
	free(ps->hash);
	free(ps);
}
