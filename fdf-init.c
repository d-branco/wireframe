/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:11:42 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 13:45:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	validate_map_name(char **argv);
static void	map_the_map(t_fdf *fdf, char *map_file);

int	input_validation(int argc, char **argv)
{
	int	result;

	result = 1;
	if (argc != 2)
	{
		if (argc == 1)
			ft_printf("No map file  provided!\n");
		if (argc > 2)
			ft_printf("Too many arguments!\n");
		result = 0;
	}
	else
		result = validate_map_name(argv);
	return (result);
}

static int	validate_map_name(char **argv)
{
	int	result;
	int	len;

	result = 1;
	len = ft_strlen(argv[1]);
	if (len <= 4)
	{
		ft_printf("Invalid map file!\n");
		result = 0;
	}
	else if ((argv[1][len - 4] != '.') || (argv[1][len - 3] != 'f')
		|| (argv[1][len - 2] != 'd') || (argv[1][len - 1] != 'f'))
	{
		ft_printf("Invalid map file!\n");
		result = 0;
	}
	if (result == 0)
		ft_printf("usage:\n./fdf <map_name>.fdf\n");
	return (result);
}

void	initialize_mlx(t_fdf *fdf, char *map_name)
{
	int	i;

	fdf->mlx = mlx_init();
	fdf->mlx_window = mlx_new_window(fdf->mlx, 960, 1040, "Hello ground!");
	fdf->img = mlx_new_image(fdf->mlx, 960, 1040);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	fdf->map = NULL;
	fdf->map_width = get_map_width(map_name);
	fdf->map_length = get_map_length(map_name);
	fdf->map = (int **) ft_calloc(fdf->map_width, sizeof(int *));
	i = 0;
	while (i < fdf->map_width)
	{
		fdf->map[i] = (int *) ft_calloc(fdf->map_length, sizeof(int));
		i++;
	}
	map_the_map(fdf, map_name);
}

static void	map_the_map(t_fdf *fdf, char *map_file)
{
	int		x;
	int		y;
	char	*line;
	char	**splitted_line;
	int		map_file_fd;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	line = get_next_line(map_file_fd);
	y = -1;
	while (++y < fdf->map_width)
	{
		x = 0;
		splitted_line = ft_split(line, ' ');
		while (x < fdf->map_length)
		{
			fdf->map[y][x] = ft_atoi(splitted_line[x]);
			x++;
		}
		free_splitted(splitted_line);
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	return ;
}
