/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/05/31 10:49:39 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TESTS_H
# define FT_TESTS_H

void	ft_print_stack(t_stack *s);
void	ft_is_sorted(t_stack *s);
void	ft_print_pseudo_sorted(t_ps *pseudo_sorted);
void	ft_print_checks(t_list ***checks, int size);
void	ft_print_strat(t_nb *nb);

#endif