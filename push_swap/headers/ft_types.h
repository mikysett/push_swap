/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/24 00:18:40 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

# define CLR_WHITE	"\033[0;37m"
# define CLR_BLACK	"\033[0;30m"
# define CLR_GRAY	"\033[30;1m"
# define CLR_RED	"\033[0;31m"
# define CLR_GREEN	"\033[0;32m"
# define CLR_YELLOW	"\033[0;33m"
# define CLR_BLUE	"\033[0;34m"
# define CLR_PURPLE	"\033[0;35m"
# define CLR_CYAN	"\033[0;36m"

# define DEBUG_MODE 0
# if DEBUG_MODE == 1
#  define DEBUG_CODE(x) x
# else
#  define DEBUG_CODE(x)
# endif

# define SCORE_THRESHOLD	0.90
# define OP_MAX_CHECK		10
# define OP_BUF_SIZE		1000
# define OP_SUB_BUF			10
# define MAX_REC			100000L


typedef enum	e_s_name
{
	stack_a = 0,
	stack_b = 1
}				t_s_name;

typedef enum	e_pos_type
{
	initial_pos,
	sorted_pos
}				t_pos_type;

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

typedef enum	e_strat_type
{
	by_rr,
	by_rrr,
	by_ra_rrb,
	by_rra_rb
}				t_strat_type;

typedef struct	s_op_info
{
	t_op_type	type;
	int			a_size;
	int			b_size;
}				t_op_info;

typedef struct	s_sort_strat
{
	int				b_r;
	int				b_rr;
	int				a_r;
	int				a_rr;
	t_strat_type	type;
}				t_sort_strat;

typedef struct	s_nb
{
	int				nb;
	int				lis_lvl;
	int				sort_pos;
	int				init_pos;
	int				range;
	t_sort_strat	strat;
	int				mov_to_sort;
	
	bool			in_range;
}				t_nb;

typedef struct	s_stack
{
	t_nb	*stack;
	int		size;
	int		top;
	
	int		nb_sorted;
	int		size_unsorted;

	// Only used in Stack A
	int		lis_lvl;
}				t_stack;


// TODO remove after tests (only for debug and opti)
// typedef struct	s_ops_stats
// {
// 	int	fill_b;
// 	int	sort_not_in_range;
// 	int	reduce_not_in_range;
// 	int	organize_not_in_range;
// 	int	merge_stacks;
// 	int	rotate_sorted;
// }				t_ops_stats;

typedef struct	s_data
{
	t_stack		s_a;
	t_stack		s_b;
	bool		wait_to_swap;
}				t_data;

typedef struct	s_ps
{
	char	*hash;
	int		size;
	int		start_pos;
	int		chunk_size;
	int		protection_lvl;
	int		score;
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
}				t_ps_rec;

typedef struct	s_merge_info
{
	t_stack		*s_in;
	t_stack		*s_from;
	int			lvl_in;
	int			lvl_from;
	t_s_name	in_name;
	bool		reversed_merge;
	bool		reverse_into_b;
}				t_merge_info;

#endif
