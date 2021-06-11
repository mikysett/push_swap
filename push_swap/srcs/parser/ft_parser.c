/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:59:04 by msessa            #+#    #+#             */
/*   Updated: 2021/05/19 16:43:42 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_parser(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnumber(argv[i]) || !ft_isint(argv[i]))
			ft_exit_failure();
		i++;
	}
}

bool	ft_isnumber(char *nb)
{
	if (*nb == '-')
		nb++;
	if (!*nb)
		return (false);
	while (*nb)
	{
		if (*nb < '0' || *nb > '9')
			return (false);
		nb++;
	}
	return (true);
}

bool	ft_isint(char *nb)
{
	size_t	nb_size;
	char	*nb_char;

	nb_size = ft_strlen(nb);
	nb_char = ft_itoa(ft_atoi(nb));
	if (nb_size != ft_strlen(nb_char)
		|| ft_strncmp(nb, nb_char, nb_size))
	{
		free(nb_char);
		return (false);
	}
	free(nb_char);
	return (true);
}