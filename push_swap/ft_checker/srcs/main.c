/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:03:00 by msessa            #+#    #+#             */
/*   Updated: 2021/05/24 00:28:38 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_checker.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
		return (0);
	ft_parser(argc, argv);
	ft_init_data(argc, argv, &data);
	ft_set_pos(&data.s_a, initial_pos);
	ft_set_sort_pos(&data);
	ft_checker(&data);
	ft_free_data(&data);
	return (0);
}
