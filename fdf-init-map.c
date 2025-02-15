/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-init-map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:20:02 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/15 22:00:10 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_initialize(t_fdf *fdf, char *map_name)
{
	int	i;

	fdf->map = NULL;
	fdf->map_width = get_map_width(map_name);
	fdf->map_length = get_map_length(map_name);
	fdf->map = (int **) ft_calloc(fdf->map_width, sizeof(int *));
	i = 0;
	while (i < fdf->map_width)
	{
		fdf->map[i] = (int *) ft_calloc(fdf->map_length, sizeof(int));
		if (fdf->map[i] == NULL)
			exit (5);
		i++;
	}
	map_the_map(fdf, map_name);
	map_the_peaks(fdf);
	fdf->angle = 30;
	fdf->center_x = fdf->win_width / 2;
	fdf->center_y = fdf->win_height / 2;
	fdf->trans_x = 0;
	fdf->trans_y = 0;
	fdf->projection = 0;
	fit_map(fdf);
}

void	fit_map(t_fdf *fdf)
{
	if ((fdf->win_width) > (fdf->win_height))
	{
		fdf->edge_len = (int)(fdf->win_width
				/ ((fdf->map_length + fdf->map_width + 2) * cos(M_PI / 6)));
	}
	else
	{
		fdf->edge_len = (int)(fdf->win_height
				/ ((fdf->map_length + fdf->map_width + 2) * cos(M_PI / 6)));
	}
}

void	map_the_map(t_fdf *fdf, char *map_file)
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

void	map_the_peaks(t_fdf *fdf)
{
	int	y;
	int	x;

	fdf->map_highest = fdf->map[0][0];
	fdf->map_lowest = fdf->map[0][0];
	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			if (fdf->map[y][x] < fdf->map_lowest)
				fdf->map_lowest = fdf->map[y][x];
			if (fdf->map[y][x] > fdf->map_highest)
				fdf->map_highest = fdf->map[y][x];
			x++;
		}
		y++;
	}
	ft_printf("Maps highest peak: %i\n", fdf->map_highest);
	ft_printf("Maps lowest peak: %i\n", fdf->map_lowest);
}
