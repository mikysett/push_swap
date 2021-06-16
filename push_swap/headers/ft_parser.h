/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:42:57 by msessa            #+#    #+#             */
/*   Updated: 2021/06/16 19:03:09 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARTSER_H
# define FT_PARTSER_H

void	ft_parser(int argc, char **argv);
bool	ft_isnumber(char *nb);
bool	ft_isint(char *nb);
bool	ft_duplicated_nb(t_stack *s);

#endif
