/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/05/28 14:01:33 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_free_pseudo_sort(t_ps *pseudo_sort)
{
	free(pseudo_sort->hash);
	free(pseudo_sort);
}

static bool	ft_set_result(t_ps_rec *rec, bool circled, int first_nb, int size)
{
	int	i;
	int	j;

	rec->res = malloc(sizeof(t_ps));
	if (rec->res)
		rec->res->hash = ft_calloc(size, sizeof(bool));
	if (!rec->res || !rec->res->hash)
		ft_exit_failure();
	rec->res->hash[0] = true;
	rec->res->score = 1;
	rec->res->size = size;
	rec->res->circled = circled;
	rec->res->lower_nb = first_nb;
	if (!rec->best)
		return (true);
	i = size - 1;
	j = rec->best->size - 1;
	while (j >= 0)
		rec->res->hash[i--] = rec->best->hash[j--];
	rec->res->score += rec->best->score;
	// ft_free_pseudo_sort(rec->best);
	return (true);
}

static void	ft_take_best(t_ps **best, t_ps **new)
{
	if ((*best) == 0 || (*best)->score < (*new)->score)
		(*best) = (*new);

	// if ((*best) == 0)
	// 	(*best) = (*new);
	// else if ((*best)->score < (*new)->score)
	// {
	// 	ft_free_pseudo_sort(*best);
	// 	(*best) = (*new);
	// }
	// else
	// 	ft_free_pseudo_sort(*new);
}

void	ft_init_ps_rec(t_ps_rec *rec, t_stack *s, bool circled, int pos)
{
	rec->best = 0;
	rec->new = 0;
	rec->pos_nb = s->stack[pos].nb;
	rec->s_size = s->size;
	rec->circled = circled;
}

void	ft_print_checks(t_list ***checks, int size)
{
	t_list	*curr;
	t_ps	*curr_ps;
	int		i;
	int		nb_checks;

	i = 0;
	nb_checks = 0;
	while (i < size)
	{
		printf("%sChecks for: %d%s\n", CLR_YELLOW, i, CLR_WHITE);
		curr = *checks[i];
		while (curr)
		{
			curr_ps = (t_ps *)curr->content;
			printf("%scircled: %d, first_nb: %6d%s - ",
				CLR_BLUE,
				curr_ps->circled,
				curr_ps->lower_nb,
				CLR_WHITE);
			ft_print_pseudo_sorted(curr_ps);
			curr = curr->next;
			nb_checks++;
		}
		i++;
	}
	printf("Total checks: %d\n", nb_checks);
}

void	ft_save_check(t_list **checks, t_ps_rec *rec)
{
	t_list	*new_el;

	new_el = ft_lstnew((void *)rec->new);
	if (!new_el)
		ft_exit_failure();
	ft_lstadd_front(checks, new_el);
}

t_ps	*ft_best_checked(t_list **checks, int circled, int first_nb)
{
	t_list	*curr;
	t_ps	*curr_ps;
	t_ps	*best;

	best = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if ((!curr_ps->circled && !circled)
			|| (curr_ps->circled && circled && curr_ps->lower_nb == first_nb))
		{
			if (best == 0 || best->score < curr_ps->score)
			{
				best = curr_ps;
				printf("%sALREADY CHECKED, size: %d\n%s", CLR_GREEN, curr_ps->size, CLR_WHITE);
			}
		}
		curr = curr->next;
	}
	return (best);
}

static t_ps	*ft_do_pseudo_sort(t_ps_data *ps_data, bool circled, int pos,
	int first_nb)
{
	t_ps_rec	rec;
	int			i;
	int			i_nb;

	ft_init_ps_rec(&rec, ps_data->s, circled, pos);
	ps_data->recursions++;
	i = pos + 1;
	while (i < rec.s_size)
	{
		i_nb = ps_data->s->stack[i].nb;
		if ((i_nb < rec.pos_nb && (circled == false
			|| (circled == true && i_nb > first_nb)))
				|| (circled == false && i_nb > first_nb))
		{
			if (i_nb > rec.pos_nb)
				circled = true;
			rec.new = ft_best_checked(ps_data->checks[i], circled, first_nb);
			if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(ps_data, circled, i, first_nb);
				ft_save_check(ps_data->checks[i], &rec);
			}
			ft_take_best(&rec.best, &rec.new);
			if (ps_data->recursions > 1000000L)
			{
				printf("%sREC: %ld%s\n", CLR_RED, ps_data->recursions, CLR_WHITE);
				break;
			}
			if (rec.best->score > rec.s_size - pos)
				break;
		}
		i++;
	}
	if (!ft_set_result(&rec, rec.circled, first_nb, rec.s_size - pos))
		ft_exit_failure();
	return (rec.res);
}

static void	ft_set_is_sorted(t_stack *s, t_ps *ps)
{
	int	i;
	int	j;

	i = s->size - 1;
	j = ps->size - 1;
	while (j >= 0)
	{
		if (ps->hash[j] == true)
			s->stack[i].is_sorted = true;
		i--;
		j--;
	}
}

void	ft_set_checked(bool *checked, t_ps *res, int size)
{
	int	i;
	int	j;

	i = size - 1;
	j = res->size - 1;
	while (j >= 0)
	{
		if (res->hash[j] == true)
			checked[i] = true;
		i--;
		j--;
	}
}

void	ft_init_ps_data(t_ps_data *ps_data, t_stack *s)
{
	int	i;

	ps_data->s = s;
	ps_data->best = 0;
	ps_data->new = 0;
	ps_data->recursions = 0;
	ps_data->checks = ft_calloc(s->size, sizeof(t_list **));
	if (!ps_data->checks)
		ft_exit_failure();
	i = 0;
	while (i < s->size)
	{
		ps_data->checks[i] = ft_calloc(1, sizeof(t_list *));
		if (!ps_data->checks[i])
			ft_exit_failure();
		i++;
	}
}

void	ft_pseudo_sort(t_data *data)
{
	int			i;
	bool		*checked;

	t_ps_data	ps_data;

	i = 0;
	ft_init_ps_data(&ps_data, &data->s_a);

	checked = ft_calloc(data->s_a.size, sizeof(bool));
	if (!checked)
		ft_exit_failure();

	while (i < data->s_a.size - 1)
	{
		// if (checked[i] == false)
		{
			printf("\n%sDoing pseudo sort starting at pos: %d%s - ",
				CLR_BLUE, i, CLR_WHITE);
			ps_data.new = ft_do_pseudo_sort(&ps_data, false, i,
				data->s_a.stack[i].nb);
			ps_data.recursions = 0;
			ft_set_checked(checked, ps_data.new, data->s_a.size);
			ft_print_pseudo_sorted(ps_data.new);
			ft_take_best(&ps_data.best, &ps_data.new);
			// ft_free_pseudo_sort(ps_data.new);
			if (ps_data.best->score >= data->s_a.size - i)
				break;
		}
		i++;
	}
	ft_print_checks(ps_data.checks, ps_data.s->size);
	ft_set_is_sorted(&data->s_a, ps_data.best);
	ft_free_pseudo_sort(ps_data.best);
	free(checked);
}
