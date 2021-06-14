/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:41:20 by msessa            #+#    #+#             */
/*   Updated: 2021/06/14 19:03:59 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_free_data(t_data *data)
{
	if (data->s_a.stack)
		free(data->s_a.stack);
	if (data->s_b.stack)
		free(data->s_b.stack);
	if (data->ranges)
		free(data->ranges);
}

void	ft_exit_failure(void)
{
		write(STDERR_FILENO, "Error\n", 6);
		exit(EXIT_FAILURE);
}
