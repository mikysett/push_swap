/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:27:43 by msessa            #+#    #+#             */
/*   Updated: 2021/05/29 16:00:36 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

// void	ft_free_pseudo_sort(t_ps *pseudo_sort)
// {
// 	free(pseudo_sort->hash);
// 	free(pseudo_sort);
// }

static t_ps	*ft_set_result(t_ps *best, bool circled, int first_nb, int size)
{
	int		i;
	int		j;
	t_ps	*res;

	res = malloc(sizeof(t_ps));
	if (res)
		res->hash = ft_calloc(size, sizeof(bool));
	if (!res || !res->hash)
		ft_exit_failure();
	res->hash[0] = true;
	res->score = 1;
	res->size = size;
	res->circled = circled;
	res->lower_nb = first_nb;
	if (!best)
		return (res);
	i = size - 1;
	j = best->size - 1;
	while (j >= 0)
		res->hash[i--] = best->hash[j--];
	res->score += best->score;
	// ft_free_pseudo_sort(best);
	return (res);
}

static bool	ft_is_nb_eligible(int s_i_nb, int rec_pos_nb, bool circled,
	int first_nb)
{
	if ((s_i_nb < rec_pos_nb && (circled == false
			|| (circled == true && s_i_nb > first_nb)))
				|| (circled == false && s_i_nb > first_nb))
		return (true);
	return (false);
}

static t_ps	*ft_do_pseudo_sort(t_ps_data *ps_data, bool circled, int pos,
	int first_nb)
{
	t_ps_rec	rec;
	int			i;

	ft_init_ps_rec(&rec, ps_data->s, circled, pos);
	ps_data->nb_rec++;
	i = pos;
	while (++i < rec.s_size)
		if (ft_is_nb_eligible(ps_data->s->stack[i].nb,
				rec.pos_nb, circled, first_nb))
		{
			if (ps_data->s->stack[i].nb > rec.pos_nb)
				circled = true;
			rec.new = ft_best_checked(ps_data->checks[i], circled, first_nb);
			if (!rec.new)
			{
				rec.new = ft_do_pseudo_sort(ps_data, circled, i, first_nb);
				ft_save_check(ps_data->checks[i], &rec);
			}
			ft_take_best(&rec.best, &rec.new);
			if (ps_data->nb_rec > MAX_REC || rec.best->score > rec.s_size - pos)
				break;
		}
	return (ft_set_result(rec.best, rec.circled, first_nb, rec.s_size - pos));
}

// void	ft_set_checked(bool *checked, t_ps *res, int size)
// {
// 	int	i;
// 	int	j;

// 	i = size - 1;
// 	j = res->size - 1;
// 	while (j >= 0)
// 	{
// 		if (res->hash[j] == true)
// 			checked[i] = true;
// 		i--;
// 		j--;
// 	}
// }

void	ft_pseudo_sort(t_data *data)
{
	int		i;
	int		i_nb;
	bool	circled_v;
	bool	linear_v;
	// bool		*checked;

	t_ps_data	ps_data;

	i = 0;
	ft_init_ps_data(&ps_data, &data->s_a);

	// checked = ft_calloc(data->s_a.size, sizeof(bool));
	// if (!checked)
	// 	ft_exit_failure();

	while (i < data->s_a.size - 1)
	{
		i_nb = data->s_a.stack[i].nb;
		// printf("\n%sDoing pseudo sort starting at pos: %d%s - ", CLR_BLUE, i, CLR_WHITE);
		ps_data.new = ft_abs_best_checked(ps_data.checks[i], &linear_v, &circled_v);
		if (!ps_data.new || !linear_v || !circled_v)
			ps_data.new = ft_do_pseudo_sort(&ps_data, false, i, i_nb);
		if (ps_data.nb_rec > 0)
			printf("i: %10d, nb_rec: %ld\n", i, ps_data.nb_rec);
		ps_data.nb_rec = 0;
		// To test
		// ft_print_pseudo_sorted(ps_data.new);
		ft_take_best(&ps_data.best, &ps_data.new);
		// ft_set_checked(checked, ps_data.new, data->s_a.size);
		// ft_free_pseudo_sort(ps_data.new);
		if (ps_data.best->score >= data->s_a.size - i)
			break;
		i++;
	}
	// To test
	ft_print_pseudo_sorted(ps_data.best);
	// ft_print_checks(ps_data.checks, ps_data.s->size);
	ft_set_is_sorted(&data->s_a, ps_data.best);
	data->nb_sorted = ps_data.best->score;
	ft_free_checks(&ps_data);
	// ft_free_pseudo_sort(ps_data.best);
	// free(checked);
}
