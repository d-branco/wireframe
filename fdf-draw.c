/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:13:59 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 15:15:38 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_all_the_lines(t_fdf *fdf, int y, int x);
static int	zz(t_fdf *fdf, int y, int x);

void	draw_map(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			draw_all_the_lines(fdf, y, x);
			x++;
		}
		y++;
	}
}

//ft_printf("Start    x: %i,    y: %i,    z: %i\n", start.x, start.y, start.z);
//ft_printf("End      x: %i,    y: %i,    z: %i\n", end.x, end.y, end.z);
static void	draw_all_the_lines(t_fdf *fdf, int y, int x)
{
	t_point	start;
	t_point	end;

	if (x < fdf->map_length - 1)
	{
		start = (t_point){40 * x + 100, 40 * y + 100, zz(fdf, y, x)};
		end = (t_point){40 * x + 140, 40 * y + 100, zz(fdf, y, x + 1)};
		draw_point_to_point(fdf, start, end);
	}
	if (y < fdf->map_width - 1)
	{
		start = (t_point){40 * x + 100, 40 * y + 100, zz(fdf, y, x)};
		end = (t_point){40 * x + 100, 40 * y + 140, zz(fdf, y + 1, x)};
		draw_point_to_point(fdf, start, end);
	}
}

// linear interpolation
static int	zz(t_fdf *fdf, int y, int x)
{
	int	zz;

	zz = ((fdf->map[y][x] - fdf->map_lowest) * 255)
		/ (fdf->map_highest - fdf->map_lowest);
	return (zz);
}

/*
	start = (t_point){400, 200, 255};
	end = (t_point){600, 200, 255};
	draw_point_to_point(fdf, start, end);
*/