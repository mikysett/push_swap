/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:59:05 by msessa            #+#    #+#             */
/*   Updated: 2021/06/27 22:56:46 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	ft_prepare_reversed_stacks(t_data *data);
static void	ft_chose_best_top_lvl(t_data *data);
static void	ft_chose_best_top_lvl_in_stack(t_data *data, t_stack *s,
				t_s_name s_name);
static void	ft_reverse_rotate_bottom_lvl(t_data *data, t_stack *s,
				t_s_name s_name);

void	ft_init_merge(t_data *data, t_merge_info *m)
{
	m->reversed_merge = false;
	if (ft_top_lvl_reversed(&data->s_a, data->s_a.top)
		&& ft_top_lvl_reversed(&data->s_b, data->s_b.top))
		m->reversed_merge = true;
	else
		ft_prepare_reversed_stacks(data);
	if (m->reversed_merge)
	{
		DEBUG_CODE(printf("- - - - REVERSED MERGE: %d\n", m->reverse_into_b);)
		if (m->reverse_into_b)
			m->in_name = stack_a;
		else
			m->in_name = stack_b;
		m->reverse_into_b = !m->reverse_into_b;
	}
	else if (ft_bottom_lvl_reversed(&data->s_a, 0))
		m->in_name = stack_b;
	else if (ft_bottom_lvl_reversed(&data->s_b, 0))
		m->in_name = stack_a;
	else
	{
		m->in_name = ft_stack_with_less_lvl(data);
		DEBUG_CODE(printf("ORDER DECIDED BY MORE LEVELS IN A: %d\n", m->in_name);)
	}
	ft_init_stacks_name(data, m);
	// This function needs to be reviewed deeply!
	ft_chose_best_top_lvl(data);
	// ft_chose_best_top_lvl_in_stack(data, m->s_in, m->in_name);
	if (m->s_from->size > 0)
		m->lvl_from = m->s_from->stack[m->s_from->top].lis_lvl;
	if (m->s_in->size > 0)
		m->lvl_in = m->s_in->stack[m->s_in->top].lis_lvl;

}

static void	ft_prepare_reversed_stacks(t_data *data)
{
	if (ft_top_lvl_reversed(&data->s_a, data->s_a.top))
	{
		if (ft_count_lvl(&data->s_a) == 1)
			ft_reverse_stack(data, &data->s_a, stack_a);
		else
			ft_swap_lvl(data, stack_b, &data->s_a);
	}
	else if (ft_top_lvl_reversed(&data->s_b, data->s_b.top))
	{
		if (ft_count_lvl(&data->s_b) == 1)
			ft_reverse_stack(data, &data->s_b, stack_b);
		else
			ft_swap_lvl(data, stack_a, &data->s_b);
	}
}

static void	ft_chose_best_top_lvl(t_data *data)
{
	int	top_a_lvl_size;
	int	top_b_lvl_size;
	int	delta_lvl_size;

	top_a_lvl_size = ft_get_lvl_size(&data->s_a,
		data->s_a.stack[data->s_a.top].lis_lvl);
	top_b_lvl_size = ft_get_lvl_size(&data->s_b,
		data->s_b.stack[data->s_b.top].lis_lvl);
	delta_lvl_size = ft_abs(top_a_lvl_size - top_b_lvl_size);
	if (delta_lvl_size * 2 > ft_bigger_nb(top_a_lvl_size, top_b_lvl_size))
	{
		ft_chose_best_top_lvl_in_stack(data, &data->s_a, stack_a);
		ft_chose_best_top_lvl_in_stack(data, &data->s_b, stack_b);
	}
}

static void	ft_chose_best_top_lvl_in_stack(t_data *data, t_stack *s,
	t_s_name s_name)
{
	if (ft_count_lvl(s) < 2
		|| ft_top_lvl_reversed(s, s->top)
		|| ft_bottom_lvl_reversed(s, 0))
		return ;
	if (ft_get_lvl_size(s, s->stack[s->top].lis_lvl)
		> ft_get_lvl_size(s, s->stack[0].lis_lvl) * 2)
		ft_reverse_rotate_bottom_lvl(data, s, s_name);
}

static void	ft_reverse_rotate_bottom_lvl(t_data *data, t_stack *s,
	t_s_name s_name)
{
	int	bottom_lvl;

	if (ft_count_lvl(s) <= 1)
		return ;
	bottom_lvl = s->stack[0].lis_lvl;
	while (s->stack[0].lis_lvl == bottom_lvl)
		ft_reverse_rotate_stack(data, s_name);
}
