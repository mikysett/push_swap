/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:02 by msessa            #+#    #+#             */
/*   Updated: 2021/06/11 18:42:06 by msessa           ###   ########.fr       */
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
# define CLR_PURPLE	"\033[0;35m"
# define CLR_CYAN	"\033[0;36m"

# define DEBUG_MODE 1
# if DEBUG_MODE == 1
#  define DEBUG_CODE(x) x
# else
#  define DEBUG_CODE(x)
# endif

# define SCORE_THRESHOLD	0.90
# define OP_BUF_SIZE		1000
# define OP_SUB_BUF			10
# define MAX_REC			100000L


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
	int				is_sorted;
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
	int		nb_sorted;
	int		sorting_level;
	int		smaller_sort_pos;
	int		bigger_sort_pos;

	// Used only in Stack B
	int		nb_not_in_range;
	int		unranged_in_buffer;


	int		nb_in_range;
}				t_stack;

typedef struct	s_range
{
	int	ind_start;
	int	ind_end;
	int	start_nb;
	int	end_nb;
}				t_range;

typedef struct	s_ops_stats
{
	int	fill_b;
	int	sort_not_in_range;
	int	reduce_not_in_range;
	int	organize_not_in_range;
	int	merge_stacks;
	int	rotate_sorted;
}				t_ops_stats;

typedef struct	s_data
{
	t_stack		s_a;
	t_stack		s_b;
	bool		wait_to_swap;
	t_ops_stats	stats;

	t_range		*ranges;
	int			nb_ranges;
	

	// Ideally this could be deleted at the end
	t_range		range;
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

#endif
