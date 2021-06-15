/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/06/15 22:52:24 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static t_ps	*ft_set_result(t_ps *best, int size, int pos, int first_pos)
{
	t_ps	*res;
	
	res = ft_calloc(1, sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(char));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[pos] = 1;
	res->start_pos = pos;
	res->score = 1;
	res->size = size;
	res->chunk_size = ft_chunk_size(size, pos, first_pos);
	if (!best)
		return (res);
	pos = (pos + 1) % size;
	while (pos != best->start_pos)
		pos = (pos + 1) % size;
	while (pos != first_pos)
	{
		if (best->hash[pos] != 0)
			res->hash[pos] = 1;
		pos = (pos + 1) % size;
	}
	res->score += best->score;
	best->protection_lvl--;
	return (res);
}

static t_ps	*ft_do_pseudo_sort(t_list ***checks, t_stack *s, int pos, int first_pos)
{
	t_ps_rec	rec;
	t_nb		*nb;
	int			i;

	ft_init_ps_rec(&rec, s, pos);
	i = pos + 1;
	while (i < s->size)
	{
		nb = &s->stack[i];
		if (!nb->is_sorted && nb->nb < rec.pos_nb)
		{
			// Recursion depth limit
			// if (ps_data->nb_rec > MAX_REC)
			// 	break;
			if (rec.best
				&& rec.best->score >= ft_chunk_size(s->size, i, first_pos))
				break;
			rec.new = ft_best_checked(checks[i], s->size, i, first_pos);
			if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(checks, s, i, first_pos);
				ft_save_check(checks[i], rec.new);
			}
			ft_take_best(&rec.best, &rec.new);
		}
		i++;
	}
	return (ft_set_result(rec.best, s->size, pos, first_pos));
}

bool	ft_is_level_in_check(t_ps *ps, t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->size)
	{
		if (ps->hash[i] == 1
			&& s->stack[i].is_sorted == s->sorting_level)
			return (true);
		i++;
	}
	return (false);
}

void	ft_remove_sgl_invalid(t_list **checks, t_stack *s)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;
	t_ps	*curr_ps;

	prev = 0;
	curr = *checks;
	while (curr)
	{
		curr_ps = (t_ps *)curr->content;
		if (ft_is_level_in_check(curr_ps, s))
		{
			if (!prev)
				*checks = curr->next;
			else
				prev->next = curr->next;
			next = curr->next;
			ft_lstdelone(curr, ft_free_sgl_check);
			curr = next;
			// printf("ONE BUFFER CLEANED ---<<<<<<------------\n");
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	ft_remove_invalid_checks(t_list ***checks, t_stack *s)
{
	int		i;

	i = 0;
	while (i < s->size)
	{
		ft_remove_sgl_invalid(checks[i], s);
		i++;
	}
}

void	ft_pseudo_sort(t_stack *s)
{
	int			i;
	t_ps		*best;
	t_ps		*new;
	t_list		***checks;
	int			score_threshold;

	score_threshold = s->size * SCORE_THRESHOLD;
	checks = ft_init_checks(s->size);
	while (!ft_all_sorted_set(s))
	{
		i = 0;
		best = 0;
		s->sorting_level++;
		printf("sorting_level: %d\n", s->sorting_level);
		while (i < s->size)
		{
			// if (best && best->score > score_threshold)
			// 	break;
			if (!s->stack[i].is_sorted)
			{
				new = ft_do_pseudo_sort(checks, s, i, i);
				ft_save_check(checks[i], new);
				DEBUG_CODE(
					printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
					printf("    i: %4d\n", i);
				)
				DEBUG_CODE(ft_print_pseudo_sorted(new);)
				ft_take_best(&best, &new);
			}
			i++;
		}
		if (best)
		{
			DEBUG_CODE(
				if (best)
					ft_print_pseudo_sorted(best);
			)
			ft_set_is_sorted(s, best);
			ft_remove_invalid_checks(checks, s);
		}
	}
	DEBUG_CODE(
		printf("STACK A\n");
		ft_print_stack(s);
	)
	DEBUG_CODE(ft_print_checks_nb(checks, s->size);)
	
	ft_free_checks(checks, s->size);

	// Legacy code, should be removed (after checking it's safe)
	// s->nb_sorted = best->score;
	// DEBUG_CODE(printf("nb_sorted: %d\n", best->score);)
	
	// ft_print_checks(checks, s->size);

}
