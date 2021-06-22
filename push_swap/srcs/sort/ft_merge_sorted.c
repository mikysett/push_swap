/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/22 16:28:10 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"


void	ft_merge_sorted(t_data *data)
{
	t_merge_info	merge;
	int				i;

	merge.reverse_into_b = true;
	while (data->s_b.size)
	{
		ft_compact_top(data, &data->s_a, stack_a);
		ft_compact_top(data, &data->s_b, stack_b);
		ft_init_merge(data, &merge);
		if (merge.reversed_merge)
			ft_merge_reversed(data, &merge);
		else
			ft_merge_into(data, &merge);
		DEBUG_CODE(
			ft_print_stack_ligh(data);
		)
		ft_print_ops(data, op_none);
	}
	if (ft_count_lvl(&data->s_a) > 1)
	{
		ft_invert_level(data, stack_b, &data->s_a);
		ft_merge_sorted(data);
	}
}

void	ft_init_merge(t_data *data, t_merge_info *m)
{
	if (ft_top_level_reversed(&data->s_a, data->s_a.top)
		&& ft_top_level_reversed(&data->s_b, data->s_b.top))
		m->reversed_merge = true;
	else
	{
		if (ft_top_level_reversed(&data->s_a, data->s_a.top))
		{
			if (ft_count_lvl(&data->s_a) == 1)
				ft_reverse_stack(data, &data->s_a, stack_a);
			else
				ft_invert_level(data, stack_b, &data->s_a);
		}
		else if (ft_top_level_reversed(&data->s_b, data->s_b.top))
		{
			if (ft_count_lvl(&data->s_b) == 1)
				ft_reverse_stack(data, &data->s_b, stack_b);
			else
				ft_invert_level(data, stack_a, &data->s_b);
		}
		// ft_chose_best_top_lvl(data);
		m->reversed_merge = false;
	}
	if (m->reversed_merge)
	{
		DEBUG_CODE(printf("- - - - REVERSED MERGE: %d\n", m->reverse_into_b);)
		if (m->reverse_into_b)
			m->in_name = stack_a;
		else
			m->in_name = stack_b;
		m->reverse_into_b = !m->reverse_into_b;
	}
	else if (ft_bottom_level_reversed(&data->s_a, 0))
		m->in_name = stack_a;
	else if (ft_bottom_level_reversed(&data->s_b, 0))
		m->in_name = stack_b;
	else
	{
		m->in_name = ft_stack_with_less_lvl(data);
		DEBUG_CODE(printf("ORDER DECIDED BY MORE LEVELS IN A: %d\n", m->in_name);)
	}
	if (m->in_name == stack_a)
	{
		m->s_in = &data->s_a;
		m->s_from = &data->s_b;
	}
	else
	{
		m->s_in = &data->s_b;
		m->s_from = &data->s_a;
	}
	// This function needs to be reviewed deeply!
	ft_chose_best_top_lvl(data);
	// ft_chose_best_top_lvl_in_stack(data, m->s_in, m->in_name);
	if (m->s_from->size > 0)
		m->lvl_from = m->s_from->stack[m->s_from->top].lis_lvl;
	if (m->s_in->size > 0)
		m->lvl_in = m->s_in->stack[m->s_in->top].lis_lvl;

}

void	ft_chose_best_top_lvl(t_data *data)
{
	ft_chose_best_top_lvl_in_stack(data, &data->s_a, stack_a);
	ft_chose_best_top_lvl_in_stack(data, &data->s_b, stack_b);
}

void	ft_chose_best_top_lvl_in_stack(t_data *data, t_stack *s, t_s_name s_name)
{
	if (ft_count_lvl(s) != 2
		|| ft_top_level_reversed(s, s->top)
		|| ft_bottom_level_reversed(s, 0))
		return ;
	if (ft_get_lvl_size(s, s->stack[s->top].lis_lvl)
		> ft_get_lvl_size(s, s->stack[0].lis_lvl) * 2)
		ft_reverse_rotate_bottom_lvl(data, s, s_name);
}

int		ft_get_lvl_size(t_stack *s, int lis_lvl)
{
	int	i;
	int	lvl_size;

	i = 0;
	lvl_size = 0;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl == lis_lvl)
			lvl_size++;
		i++;
	}
	return (lvl_size);
}

void	ft_reverse_rotate_bottom_lvl(t_data *data, t_stack *s, t_s_name s_name)
{
	int	bottom_lvl;

	if (ft_count_lvl(s) <= 1)
		return ;
	bottom_lvl = s->stack[0].lis_lvl;
	while (s->stack[0].lis_lvl == bottom_lvl)
		ft_reverse_rotate_stack(data, s_name);
}

bool	ft_any_reversed_in_stack(t_stack *s)
{
	int	pos;

	pos = s->top;
	while (pos >= 0)
	{
		if (ft_top_level_reversed(s, pos))
			return (true);
		pos = ft_get_next_lvl_pos(s, pos);
	}
	return (false);
}

void	ft_compact_top(t_data *data, t_stack *s, t_s_name s_name)
{
	if (s->top > 1
		&& s->stack[s->top].lis_lvl != s->stack[s->top - 1].lis_lvl
		&& !ft_top_level_reversed(s, s->top - 1)
		&& (s->top < 2
			|| s->stack[s->top - 2].lis_lvl != s->stack[s->top - 1].lis_lvl
			|| ft_can_be_in_middle(s->stack[s->top].nb,
				&s->stack[s->top - 1], &s->stack[s->top - 2])))
	{
		s->stack[s->top].lis_lvl = s->stack[s->top - 1].lis_lvl;
		ft_swap_stack(data, s_name);
	}
}

t_s_name	ft_stack_with_less_lvl(t_data *data)
{
	int	nb_lvl_a;
	int	nb_lvl_b;

	nb_lvl_a = ft_count_lvl(&data->s_a);
	nb_lvl_b = ft_count_lvl(&data->s_b);
	if (nb_lvl_a > nb_lvl_b)
		return (stack_b);
	return (stack_a);
}

int		ft_count_lvl(t_stack *s)
{
	int	i;
	int	nb_levels;
	int	curr_level;

	if (!s->size)
		return (0);
	i = 1;
	nb_levels = 1;
	curr_level = s->stack[0].lis_lvl;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl != curr_level)
		{
			nb_levels++;
			curr_level = s->stack[i].lis_lvl;
		}
		i++;
	}
	return (nb_levels);
}

bool	ft_top_level_reversed(t_stack *s, int pos)
{
	int	level;

	if (pos < 1)
		return (false);
	level = s->stack[pos].lis_lvl;
	if (s->stack[pos - 1].lis_lvl == level
		&& s->stack[pos - 1].nb < s->stack[pos].nb)
		return (true);
	return (false);
}

bool	ft_bottom_level_reversed(t_stack *s, int pos)
{
	int	level;

	if (s->size < 2)
		return (false);
	level = s->stack[pos].lis_lvl;
	if (s->stack[pos + 1].lis_lvl == level
		&& s->stack[pos + 1].nb > s->stack[pos].nb)
		return (true);
	return (false);
}

void	ft_invert_level(t_data *data, t_s_name dest, t_stack *s)
{
	int	level;

	if (s->top < 1)
		return ;
	level = s->stack[s->top].lis_lvl;
	while (s->top >= 0 && s->stack[s->top].lis_lvl == level)
		ft_push_stack(data, dest);
}

void	ft_merge_into(t_data *data, t_merge_info *m)
{
	int		from_bottom_lvl;

	from_bottom_lvl = m->s_from->stack[0].lis_lvl;
	DEBUG_CODE(printf("MERGING LEVEL: %d\n", m->lvl_from);)
	while (m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from)
	{
		if (ft_merge_from_bottom(data, m, from_bottom_lvl))
			continue;
		else if (m->s_from->stack[m->s_from->top].nb < m->s_in->stack[m->s_in->top].nb
			|| m->s_in->stack[m->s_in->top].lis_lvl != m->lvl_in)
		{
			m->s_from->stack[m->s_from->top].lis_lvl = m->lvl_in;
			ft_push_stack(data, m->in_name);
		}
		else if (ft_only_one_level(m->s_in)
			&& m->s_from->stack[m->s_from->top].nb > ft_get_biggest_nb(m->s_in))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->in_name);
	}
	ft_align_s_in(data, m);
}

bool	ft_merge_from_bottom(t_data *data, t_merge_info *m, int from_bottom_lvl)
{
	t_nb	*bottom_nb;
	t_nb	*prev_nb;
	t_nb	*next_nb;

	bottom_nb = &m->s_from->stack[0];
	DEBUG_CODE(printf("Trying to merge nb: %d\n", bottom_nb->nb);)
	if (ft_count_lvl(m->s_from) == 1
		|| (ft_get_lvl_size(m->s_from, m->s_from->stack[0].lis_lvl) > 1
			&& !ft_bottom_level_reversed(m->s_from, 0)))
		return (false);
	prev_nb = 0;
	if (m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from
		&& (m->s_in->stack[m->s_in->top].lis_lvl != m->lvl_in))
		prev_nb = &m->s_from->stack[m->s_from->top];
	else if (m->s_in->stack[0].lis_lvl == m->lvl_in)
		prev_nb = &m->s_in->stack[0];
	next_nb = 0;
	if (m->s_in->stack[m->s_in->top].lis_lvl == m->lvl_in
		&& (m->s_from->stack[m->s_from->top].lis_lvl != m->lvl_from
			|| m->s_from->stack[m->s_from->top].nb > m->s_in->stack[m->s_in->top].nb))
		next_nb = &m->s_in->stack[m->s_in->top];
	else if (m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from)
		next_nb = &m->s_from->stack[m->s_from->top];
	DEBUG_CODE(
		printf("bottom_nb: %d\n", bottom_nb->nb);
		if (prev_nb)
			printf("prev_nb: %d\n", prev_nb->nb);
		else
			printf("prev_nb: NULL\n");
		if (next_nb)
			printf("next_nb: %d\n", next_nb->nb);
		else
			printf("next_nb: NULL\n");
	)
	if (ft_can_be_in_middle(bottom_nb->nb, prev_nb, next_nb))
	{
		DEBUG_CODE(
			printf("MERGING FROM BOTTOM!\n");
		)
		m->s_from->stack[0].lis_lvl = m->lvl_in;
		ft_reverse_rotate_stack(data, !m->in_name);
		ft_push_stack(data, m->in_name);
		if (next_nb && prev_nb
			&& prev_nb->nb > next_nb->nb)
			ft_rotate_stack(data, m->in_name);
		return (true);
	}
	return (false);
}

void	ft_merge_reversed(t_data *data, t_merge_info *m)
{
	DEBUG_CODE(printf("MERGING REVERSED LEVEL: %d\n", m->lvl_from);)
	while (m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == m->lvl_from)
	{
		if (m->s_from->stack[m->s_from->top].nb > m->s_in->stack[m->s_in->top].nb
			|| m->s_in->stack[m->s_in->top].lis_lvl != m->lvl_in)
		{
			m->s_from->stack[m->s_from->top].lis_lvl = m->lvl_in;
			ft_push_stack(data, m->in_name);
		}
		else if (ft_only_one_level(m->s_in)
			&& m->s_from->stack[m->s_from->top].nb < ft_get_smallest_nb(m->s_in))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->in_name);
	}
	ft_align_s_in(data, m);
}

void	ft_merge_tail(t_data *data, t_merge_info *m,
	int lvl_to_sort, int dest_lvl)
{
	ft_rotate_sorted(data, m->in_name);
	while (m->s_from->top >= 0
		&& m->s_from->stack[m->s_from->top].lis_lvl == lvl_to_sort)
	{
		m->s_from->stack[m->s_from->top].lis_lvl = dest_lvl;
		ft_push_stack(data, m->in_name);
		ft_rotate_stack(data, m->in_name);
	}
}

bool	ft_only_one_level(t_stack *s)
{
	int	i;
	int	first_level;

	i = 1;
	if (s->size < 2)
		return (true);
	first_level = s->stack[0].lis_lvl;
	while (i < s->size)
	{
		if (s->stack[i].lis_lvl != first_level)
			return (false);
		i++;
	}
	return (true);
}

int		ft_get_biggest_nb(t_stack *s)
{
	int	biggest_nb;
	int	i;

	if (!s->size)
		return (0);
	biggest_nb = s->stack[0].nb;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb > biggest_nb)
			biggest_nb = s->stack[i].nb;
		i++;
	}
	return (biggest_nb);
}

int		ft_get_smallest_nb(t_stack *s)
{
	int	smallest_nb;
	int	i;

	if (!s->size)
		return (0);
	smallest_nb = s->stack[0].nb;
	i = 1;
	while (i < s->size)
	{
		if (s->stack[i].nb < smallest_nb)
			smallest_nb = s->stack[i].nb;
		i++;
	}
	return (smallest_nb);
}

void	ft_align_s_in(t_data *data, t_merge_info *m)
{
	if (!ft_only_one_level(m->s_in))
		while (m->s_in->stack[m->s_in->top].lis_lvl == m->lvl_in)
			ft_rotate_stack(data, m->in_name);
	else
		ft_rotate_sorted(data, m->in_name);
}
