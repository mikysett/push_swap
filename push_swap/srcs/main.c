/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:43:40 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:08:53 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (argc == 2)
	{
		if (!ft_isnumber(argv[2]) || !ft_isint(argv[2]))
			ft_exit_failure();
		return (0);
	}
	ft_parser(argc, argv);
	ft_init_data(argc, argv, &data);
	ft_set_pos(&data.s_a, initial_pos);
	ft_set_sort_pos(&data);
	ft_pseudo_sort(&data.s_a);
	DEBUG_CODE(
		printf("PSEUDO SORTING CHECKS COMPLETED\n");
		printf("Stack A initial:\n");
		ft_print_stack(&data.s_a);
	)
	ft_sort(&data);
	ft_free_data(&data);
	return (0);
}
