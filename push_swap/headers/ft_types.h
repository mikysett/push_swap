/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/05/30 17:50:56 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

# define CLR_WHITE	"\033[0;37m"
# define CLR_BLACK	"\033[0;30m"
# define CLR_RED	"\033[0;31m"
# define CLR_GREEN	"\033[0;32m"
# define CLR_YELLOW	"\033[0;33m"
# define CLR_BLUE	"\033[0;34m"

# define OP_BUF_SIZE	1000
# define MAX_REC		1000000L

typedef enum	e_op_type
{
	op_none,
	op_sa,
	op_sb,
	op_ss,
	op_pa,
	op_pb,
	op_ra,
	op_rb,
	op_rr,
	op_rra,
	op_rrb,
	op_rrr,
	op_error
}				t_op_type;

typedef struct	s_nb
{
	int		nb;
	bool	is_sorted;
	int		sort_pos;
	int		init_pos;
	int		mov_to_sort;
}				t_nb;

typedef struct	s_stack
{
	t_nb	*stack;
	int		size;
}				t_stack;

typedef struct	s_range
{
	int	lower;
	int	higher;
	int	size;
}				t_range;

typedef struct	s_data
{
	t_stack		s_a;
	// t_stack		s_a_sorted;
	t_stack		s_b;
	bool		wait_to_swap;
	int			nb_sorted;

	int			nb_moves;
}				t_data;

typedef struct	s_ps
{
	bool	*hash;
	int		score;
	int		size;
	bool	circled;
	int		lower_nb;
	
}				t_ps;

typedef struct	s_ps_data
{
	t_stack	*s;
	t_ps	*best;
	t_ps	*new;
	long	nb_rec;
	t_list	***checks;
}				t_ps_data;

typedef struct	s_ps_rec
{
	t_ps	*best;
	t_ps	*new;
	int		pos_nb;
	int		s_size;
	bool	circled;
}				t_ps_rec;

#endif
