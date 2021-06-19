/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/19 11:21:33 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

// void	ft_merge_sorted(t_data *data)
// {
// 	bool	merge_into_a;

// 	merge_into_a = true;
// 	while (data->s_b.size)
// 	{
// 		if (ft_more_levels_in_a(data))
// 			merge_into_a = false;
// 		else
// 			merge_into_a = true;
// 		if (merge_into_a)
// 		{
// 			DEBUG_CODE(printf("MERGING B INTO A\n");)
// 			if (ft_level_reversed(&data->s_b, data->s_b.size - 1))
// 			{
// 				if (ft_count_lvl(&data->s_b) == 1)
// 					ft_reverse_stack(data, &data->s_b, false);
// 				else
// 					ft_invert_level(data, merge_into_a, &data->s_b);
// 			}
// 			else if (ft_level_reversed(&data->s_a, data->s_a.size - 1))
// 				ft_invert_level(data, !merge_into_a, &data->s_b);
// 			else
// 				ft_merge_into(data, merge_into_a, &data->s_a, &data->s_b);
// 		}
// 		else
// 		{
// 			DEBUG_CODE(printf("MERGING A INTO B\n");)
// 			if (ft_level_reversed(&data->s_a, data->s_a.size - 1))
// 				ft_invert_level(data, merge_into_a, &data->s_a);
// 			else if (ft_level_reversed(&data->s_b, data->s_b.size - 1))
// 			{
// 				if (ft_count_lvl(&data->s_b) == 1)
// 					ft_reverse_stack(data, &data->s_b, false);
// 				else
// 					ft_invert_level(data, !merge_into_a, &data->s_b);
// 			}
// 			else
// 				ft_merge_into(data, merge_into_a, &data->s_b, &data->s_a);
// 		}
// 		DEBUG_CODE(
// 			ft_print_stack_ligh(data);
// 		)
// 	}
// }

// void	ft_merge_sorted(t_data *data)
// {
// 	t_merge_info	merge;

// 	while (data->s_b.size)
// 	{
// 		if (ft_more_levels_in_a(data))
// 		{
// 			merge.s_in = &data->s_b;
// 			merge.s_from = &data->s_a;
// 			merge.into_a = false;
// 		}
// 		else
// 		{
// 			merge.s_in = &data->s_a;
// 			merge.s_from = &data->s_b;
// 			merge.into_a = true;
// 		}

// 		if (ft_level_reversed(merge.s_from, merge.s_from->size - 1))
// 		{
// 			if (merge.into_a && ft_count_lvl(merge.s_from) == 1)
// 				ft_reverse_stack(data, merge.s_from, false);
// 			else
// 				ft_invert_level(data, merge.into_a, merge.s_from);
// 		}
// 		else if (ft_level_reversed(merge.s_in, merge.s_in->size - 1))
// 		{
// 			if (!merge.into_a && ft_count_lvl(merge.s_in) == 1)
// 				ft_reverse_stack(data, merge.s_in, false);
// 			else
// 				ft_invert_level(data, !merge.into_a, merge.s_in);
// 		}
// 		else
// 			ft_merge_into(data, merge.into_a, merge.s_in, merge.s_from);
// 		DEBUG_CODE(
// 			ft_print_stack_ligh(data);
// 		)
// 	}
// }

// void	ft_merge_sorted(t_data *data)
// {
// 	t_merge_info	merge;

// 	while (data->s_b.size)
// 	{
// 		if (ft_more_levels_in_a(data))
// 		{
// 			merge.s_in = &data->s_b;
// 			merge.s_from = &data->s_a;
// 			merge.into_a = false;
// 		}
// 		else
// 		{
// 			merge.s_in = &data->s_a;
// 			merge.s_from = &data->s_b;
// 			merge.into_a = true;
// 		}
// 		merge.lvl_from = merge.s_from->stack[merge.s_from->size - 1].is_sorted;
// 		merge.lvl_in = merge.s_in->stack[merge.s_in->size - 1].is_sorted;

// 		if (ft_level_reversed(merge.s_from, merge.s_from->size - 1))
// 		{
// 			if (merge.into_a && ft_count_lvl(merge.s_from) == 1)
// 				ft_reverse_stack(data, merge.s_from, false);
// 			else
// 				ft_invert_level(data, merge.into_a, merge.s_from);
// 		}
// 		else if (ft_level_reversed(merge.s_in, merge.s_in->size - 1))
// 		{
// 			if (!merge.into_a && ft_count_lvl(merge.s_in) == 1)
// 				ft_reverse_stack(data, merge.s_in, false);
// 			else
// 				ft_invert_level(data, !merge.into_a, merge.s_in);
// 		}
// 		else
// 			ft_merge_into(data, merge);
// 		DEBUG_CODE(
// 			ft_print_stack_ligh(data);
// 		)
// 	}
// }

void	ft_merge_sorted(t_data *data)
{
	t_merge_info	merge;
	int	i;
	while (data->s_b.size)
	{
		ft_compact_top(data, &data->s_a, true);
		ft_compact_top(data, &data->s_b, false);
		ft_init_merge(data, &merge);

		if (ft_level_reversed(merge.s_from, merge.s_from->size - 1)
			&& ft_level_reversed(merge.s_in, merge.s_in->size - 1))
		{
			ft_merge_reversed(data, &merge);
		}
		else if (ft_level_reversed(merge.s_in, merge.s_in->size - 1))
		{
			if (!merge.into_a && ft_count_lvl(merge.s_in) == 1)
				ft_reverse_stack(data, merge.s_in, false);
			else
				ft_invert_level(data, !merge.into_a, merge.s_in);
		}
		else
			ft_merge_into(data, &merge);
		DEBUG_CODE(
			ft_print_stack_ligh(data);
		)
		ft_print_ops(data, op_none);
		// i++;
		// if (i == 10)
		// 	ft_exit_failure();
	}
}

void	ft_init_merge(t_data *data, t_merge_info *m)
{
	// if (ft_level_reversed(&data->s_a, data->s_a.size - 1)
	// 	&& !ft_level_reversed(&data->s_b, data->s_b.size - 1))
	// {
	// 	DEBUG_CODE(printf("INVERTING A FIRST LEVEL\n");)
	// 	if (ft_count_lvl(&data->s_a) == 1)
	// 		ft_reverse_stack(data, &data->s_a, true);
	// 	else
	// 		ft_invert_level(data, false, &data->s_a);
	// }
	// else if(ft_level_reversed(&data->s_b, data->s_b.size - 1)
	// 	&& !ft_level_reversed(&data->s_a, data->s_a.size - 1))
	// {
	// 	DEBUG_CODE(printf("INVERTING B FIRST LEVEL\n");)
	// 	if (ft_count_lvl(&data->s_b) == 1)
	// 		ft_reverse_stack(data, &data->s_b, false);
	// 	else
	// 		ft_invert_level(data, true, &data->s_b);
	// }



	if (ft_any_reversed_in_stack(&data->s_b))
	{
		if (ft_level_reversed(&data->s_a, data->s_a.size - 1)
			|| ft_level_reversed(&data->s_b, data->s_b.size - 1))
			m->into_a = false;
		else
			m->into_a = true;
		DEBUG_CODE(printf("ORDER DECIDED BY REVERSED LEVEL: %d\n", m->into_a);)
	}
	else
	{
		m->into_a = !ft_more_levels_in_a(data);
		DEBUG_CODE(printf("ORDER DECIDED BY MORE LEVELS IN A: %d\n", m->into_a);)
	}
	if (!m->into_a)
	{
		m->s_in = &data->s_b;
		m->s_from = &data->s_a;
	}
	else
	{
		m->s_in = &data->s_a;
		m->s_from = &data->s_b;
	}
	if (m->s_from->size > 0)
		m->lvl_from = m->s_from->stack[m->s_from->size - 1].is_sorted;
	if (m->s_in->size > 0)
		m->lvl_in = m->s_in->stack[m->s_in->size - 1].is_sorted;

}

bool	ft_any_reversed_in_stack(t_stack *s)
{
	int	pos;

	pos = s->size - 1;
	while (pos >= 0)
	{
		if (ft_level_reversed(s, pos))
			return (true);
		pos = ft_get_next_lvl_pos(s, pos);
	}
	return (false);
}

void	ft_compact_top(t_data *data, t_stack *s, bool is_stack_a)
{
	int	top;

	top = s->size - 1;
	if (top > 1
		&& s->stack[top].is_sorted != s->stack[top - 1].is_sorted
		&& !ft_level_reversed(s, top - 1)
		&& (top < 2
			|| s->stack[top - 2].is_sorted != s->stack[top - 1].is_sorted
			|| ft_can_be_in_middle(s->stack[top].nb,
				&s->stack[top - 1], &s->stack[top - 2])))
	{
		s->stack[top].is_sorted = s->stack[top - 1].is_sorted;
		ft_swap_stack(data, is_stack_a);
	}
}

bool	ft_more_levels_in_a(t_data *data)
{
	int	nb_lvl_a;
	int	nb_lvl_b;

	nb_lvl_a = ft_count_lvl(&data->s_a);
	nb_lvl_b = ft_count_lvl(&data->s_b);
	if (nb_lvl_a > nb_lvl_b)
		return (true);
	return (false);
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
	curr_level = s->stack[0].is_sorted;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted != curr_level)
		{
			nb_levels++;
			curr_level = s->stack[i].is_sorted;
		}
		i++;
	}
	return (nb_levels);
}

bool	ft_level_reversed(t_stack *s, int pos)
{
	int	level;

	if (pos < 1)
		return (false);
	level = s->stack[pos].is_sorted;
	if (s->stack[pos - 1].is_sorted == level
		&& s->stack[pos - 1].nb < s->stack[pos].nb)
		return (true);
	return (false);
}

void	ft_invert_level(t_data *data, bool merge_into_a, t_stack *s)
{
	int	top;
	int	level;

	top = s->size - 1;
	if (top < 1)
		return ;
	level = s->stack[top].is_sorted;
	while (top >= 0 && s->stack[top].is_sorted == level)
	{
		ft_push_stack(data, merge_into_a);
		top--;
	}
}

void	ft_merge_into(t_data *data, t_merge_info *m)
{
	int		from_bottom_lvl;

	from_bottom_lvl = m->s_from->stack[0].is_sorted;
	ft_update_tops(m);
	DEBUG_CODE(printf("MERGING LEVEL: %d\n", m->lvl_from);)
	while (m->top_from >= 0
		&& m->s_from->stack[m->top_from].is_sorted == m->lvl_from)
	{
	// // HARDCODED TO TEST
	// if (data->s_a.stack[data->s_a.size - 1].nb == 92
	// 	&& data->s_a.stack[data->s_a.size - 2].nb == 88)
	// {
	// 	data->s_a.stack[data->s_a.size - 2].is_sorted = 9;
	// 	ft_swap_a(data);
	// }

		if (ft_merge_from_bottom(data, m, from_bottom_lvl))
			continue;
		else
		if (m->s_from->stack[m->top_from].nb < m->s_in->stack[m->top_in].nb
			|| m->s_in->stack[m->top_in].is_sorted != m->lvl_in)
		{
			m->s_from->stack[m->top_from].is_sorted = m->lvl_in;
			ft_push_stack(data, m->into_a);
		}
		else if (ft_only_one_level(m->s_in)
			&& m->s_from->stack[m->top_from].nb > ft_get_biggest_nb(m->s_in))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->into_a);
		ft_update_tops(m);
	}
	ft_align_s_in(data, m);
}

bool	ft_merge_from_bottom(t_data *data, t_merge_info *m, int from_bottom_lvl)
{
	// if (!ft_only_one_level(m->s_from)
	// 	&& m->s_in->stack[m->top_in].is_sorted == m->lvl_in
	// 	&& m->s_from->stack[0].is_sorted == from_bottom_lvl
	// 	&& m->s_from->stack[0].nb < m->s_in->stack[m->top_in].nb
	// 	&& m->s_from->stack[0].nb < m->s_from->stack[m->top_from].nb)
	// {
	// 	m->s_from->stack[0].is_sorted = m->lvl_in;
	// 	ft_reverse_rotate_stack(data, !m->into_a);
	// 	ft_push_stack(data, m->into_a);
	// 	ft_update_tops(m);
	// 	return (true);
	// 	// ft_print_stack_ligh(data);
	// }
	// return (false);

	// BUGS WITH CIRCLING SCENARIOS
	t_nb	*bottom_nb;
	t_nb	*prev_nb;
	t_nb	*next_nb;

	bottom_nb = &m->s_from->stack[0];
	prev_nb = 0;
	if (ft_count_lvl(m->s_from) == 1)
		return (false);
	if (m->s_from->stack[m->top_from].is_sorted == m->lvl_from
		&& (m->s_in->stack[m->top_in].is_sorted != m->lvl_in
			|| m->s_from->stack[m->top_from].nb < m->s_in->stack[m->top_in].nb))
		prev_nb = &m->s_from->stack[m->top_from];
	else if (m->s_in->stack[0].is_sorted == m->lvl_in)
		prev_nb = &m->s_in->stack[0];
	next_nb = 0;
	if (m->s_in->stack[m->top_in].is_sorted == m->lvl_in)
		next_nb = &m->s_in->stack[m->top_in];
	else if (m->s_from->stack[m->top_from].is_sorted == m->lvl_from)
		next_nb = &m->s_from->stack[m->top_from];
	if (ft_can_be_in_middle(bottom_nb->nb, prev_nb, next_nb))
	{
		DEBUG_CODE(
				printf("MERGING FROM BOTTOM!\n");
			if (prev_nb)
				printf("prev_nb: %d\n", prev_nb->nb);
			else
				printf("prev_nb: NULL\n");
			if (next_nb)
				printf("next_nb: %d\n", next_nb->nb);
			else
				printf("next_nb: NULL\n");
		)
		m->s_from->stack[0].is_sorted = m->lvl_in;
		ft_reverse_rotate_stack(data, !m->into_a);
		ft_push_stack(data, m->into_a);
		ft_update_tops(m);
		// DEBUG_CODE(ft_print_stack_ligh(data);)
		return (true);
	}
	return (false);
}

void	ft_merge_reversed(t_data *data, t_merge_info *m)
{
	ft_update_tops(m);
	DEBUG_CODE(printf("MERGING REVERSED LEVEL: %d\n", m->lvl_from);)
	while (m->top_from >= 0
		&& m->s_from->stack[m->top_from].is_sorted == m->lvl_from)
	{
		if (m->s_from->stack[m->top_from].nb > m->s_in->stack[m->top_in].nb
			|| m->s_in->stack[m->top_in].is_sorted != m->lvl_in)
		{
			m->s_from->stack[m->top_from].is_sorted = m->lvl_in;
			ft_push_stack(data, m->into_a);
		}
		else if (ft_only_one_level(m->s_in)
			&& m->s_from->stack[m->top_from].nb < ft_get_smallest_nb(m->s_in))
			ft_merge_tail(data, m, m->lvl_from, m->lvl_in);
		else
			ft_rotate_stack(data, m->into_a);
		ft_update_tops(m);
	}
	ft_align_s_in(data, m);
}

void	ft_merge_tail(t_data *data, t_merge_info *m,
	int lvl_to_sort, int dest_lvl)
{
	m->top_from = m->s_from->size - 1;
	ft_rotate_sorted(data, m->s_in, m->into_a);
	while (m->top_from >= 0
		&& m->s_from->stack[m->top_from].is_sorted == lvl_to_sort)
	{
		m->s_from->stack[m->top_from].is_sorted = dest_lvl;
		ft_push_stack(data, m->into_a);
		ft_rotate_stack(data, m->into_a);
		m->top_from = m->s_from->size - 1;
	}
}

bool	ft_only_one_level(t_stack *s)
{
	int	i;
	int	first_level;

	i = 1;
	if (s->size < 2)
		return (true);
	first_level = s->stack[0].is_sorted;
	while (i < s->size)
	{
		if (s->stack[i].is_sorted != first_level)
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
	m->top_in = m->s_in->size - 1;
	if (!ft_only_one_level(m->s_in))
		while (m->s_in->stack[m->top_in].is_sorted == m->lvl_in)
			ft_rotate_stack(data, m->into_a);
	else
		ft_rotate_sorted(data, m->s_in, m->into_a);
}

void	ft_update_tops(t_merge_info *m)
{
	m->top_in = m->s_in->size - 1;
	m->top_from = m->s_from->size - 1;
}