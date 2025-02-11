/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:13:59 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 17:16:34 by abessa-m         ###   ########.fr       */
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
		ft_printf("map: ");
		while (x < fdf->map_length)
		{
			ft_printf("%3i", fdf->map[y][x]);
			draw_all_the_lines(fdf, y, x);
			x++;
		}
		ft_printf("\n");
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
		start = (t_point){16 * x + 430 - 16 * y,
			16 * x + 16 * y + 40 - (zz(fdf, y, x) / 8), zz(fdf, y, x)};
		end = (t_point){16 * x + 430 - 16 * y + 16, 16 * x + 16 * y + 40 + 16
			- (zz(fdf, y, x + 1) / 8), zz(fdf, y, x + 1)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
	if (y < fdf->map_width - 1)
	{
		start = (t_point){16 * x + 430 - 16 * y,
			16 * x + 16 * y + 40 - (zz(fdf, y, x) / 8), zz(fdf, y, x)};
		end = (t_point){16 * x + 430 - 16 * y - 16, 16 * x + 16 * y + 40 + 16
			- (zz(fdf, y + 1, x) / 8), zz(fdf, y + 1, x)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
}

// linear interpolation
static int	zz(t_fdf *fdf, int y, int x)
{
	int	zz;

	zz = ((fdf->map[y][x] - fdf->map_lowest) * 255)
		/ (fdf->map_highest - fdf->map_lowest);
	if (zz < 0)
		zz = 0;
	if (zz > 255)
		zz = 255;
	return (zz);
}

/*
	start = (t_point){400, 200, 255};
	end = (t_point){600, 200, 255};
	draw_point_to_point(fdf, start, end);
*/