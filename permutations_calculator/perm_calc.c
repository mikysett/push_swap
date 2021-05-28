/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:30:49 by msessa            #+#    #+#             */
/*   Updated: 2021/05/27 18:04:58 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

long long	ft_factorial(int nb)
{
	int			i;
	long long	res;

	i = 2;
	res = 1;
	while (i <= nb)
		res *= i++;
	return (res);
}

void	ft_error_exit(void)
{
	printf("Permutations calculator:\n");
	printf("Usage: ./perm_calc [STACK SIZE]\n");
	printf("[STACK SIZE] should be an integer > 1\n");
	exit(EXIT_FAILURE);
}

void	ft_set_dir_name(char *dir_name, char *file_name,
	int s_size, long long tot_perm)
{
	char	s_size_str[1000];
	char	tot_perm_str[1000];

	*s_size_str = '\0';
	*tot_perm_str = '\0';
	sprintf(s_size_str, "%d", s_size);
	sprintf(tot_perm_str, "%lld", tot_perm);

	dir_name[0] = '\0';
	strcat(dir_name, "./");
	strcat(dir_name, s_size_str);
	strcat(dir_name, "_");
	strcat(dir_name, tot_perm_str);

	file_name[0] = '\0';
	strcat(file_name, s_size_str);
	strcat(file_name, "_");
	strcat(file_name, tot_perm_str);
	strcat(file_name, "_");
}

void	ft_create_folder(char *dir_name)
{
	struct stat st = {0};

	if (stat(dir_name, &st) == -1 && mkdir(dir_name, 0777))
	{
		printf("Error creating the directory\n");
		ft_error_exit();
	}
}

bool	ft_is_nb_available(int *result, int nb, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		if (result[i] == nb)
			return (false);
		i++;
	}
	return (true);
}

void	ft_save_file(int *result, int size,
	char *dir_name, char *file_name, int nb_files)
{
	static char	full_path[2000];
	char		nb_files_str[1000];
	FILE		*fd;
	int			i;

	sprintf(nb_files_str, "%d", nb_files);
	full_path[0] = '\0';
	strcat(full_path, dir_name);
	strcat(full_path, "/");
	strcat(full_path, file_name);
	strcat(full_path, nb_files_str);
	fd = fopen(full_path, "w");
	if (!fd)
	{
		printf("Error saving output in a file!\n");
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		fprintf(fd, "%d ", result[i]);
		i++;
	}
	fclose(fd);
}

void	write_perms(int *result, int position, int size, char *dir_name, char *file_name)
{
	static int	nb_files = 1;

	int	nb_sel = 1;
	while (nb_sel <= size)
	{
		if (ft_is_nb_available(result, nb_sel, position + 1))
		{
			result[position] = nb_sel;
			if (position + 1 == size)
			{
				ft_save_file(result, size, dir_name, file_name, nb_files);
				nb_files++;
				result[position] = 0;
			}
			else
				write_perms(result, position + 1, size, dir_name, file_name);
		}
		nb_sel++;
	}
	result[position] = 0;
}

int	main(int argc, char **argv)
{
	int			s_size;
	long long	tot_perm;
	char		dir_name[1000];
	char		file_name[1000];
	int			*result;

	if (argc != 2)
		ft_error_exit();
	s_size = atoi(argv[1]);
	if (s_size < 2)
		ft_error_exit();
	tot_perm = ft_factorial(s_size);
	result = calloc(s_size, sizeof(int));
	printf("Tot permutations: %lld\n", tot_perm);
	ft_set_dir_name(dir_name, file_name, s_size, tot_perm);
	ft_create_folder(dir_name);
	write_perms(result, 0, s_size, dir_name, file_name);
	free(result);
	return (0);
}
