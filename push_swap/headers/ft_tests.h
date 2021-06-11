/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 17:48:16 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TESTS_H
# define FT_TESTS_H

void	ft_print_stack(t_stack *s);
void	ft_is_sorted(t_stack *s);
void	ft_print_pseudo_sorted(t_ps *pseudo_sorted);
void	ft_print_checks(t_list ***checks, int size);
void	ft_print_strat(t_nb *nb);
void	ft_print_data_range(t_data *data);
void	ft_print_checks_nb(t_list ***checks, int s_a_size);
void	ft_print_ranges(t_data *data);
void	ft_print_stats(t_data *data);

#endif