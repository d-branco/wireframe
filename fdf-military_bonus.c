/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-military_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:34:54 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/16 09:35:00 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	projection_paralel(t_fdf *fdf)
{
	int	y;
	int	x;

	fdf->center_x = fdf->trans_x + (fdf->win_width / 2)
		- ((fdf->edge_len * fdf->map_length / 2)
			* cos(((fdf->angle) * M_PI) / 180)
			- (fdf->edge_len * fdf->map_width / 2)
			* sin(((fdf->angle) * M_PI) / 180));
	fdf->center_y = fdf->trans_y + (fdf->win_height / 2)
		- (+(fdf->edge_len * fdf->map_length / 2)
			* sin(((fdf->angle) * M_PI) / 180)
			+ (fdf->edge_len * fdf->map_width / 2)
			* cos(((fdf->angle) * M_PI) / 180));
	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			draw_lines_paralel_projection(fdf, y, x);
			x++;
		}
		y++;
	}
}

//ft_printf("Start    x: %i,    y: %i,    z: %i\n", start.x, start.y, start.z);
//ft_printf("End      x: %i,    y: %i,    z: %i\n", end.x, end.y, end.z);
void	draw_lines_paralel_projection(t_fdf *fdf, int y, int x)
{
	if (x < fdf->map_length - 1)
		formula_x_pp(fdf, y, x);
	if (y < fdf->map_width - 1)
		formula_y_pp(fdf, y, x);
}

void	formula_y_pp(t_fdf *fdf, int y, int x)
{
	t_point	start;
	t_point	end;

	start = (t_point){(fdf->center_x) + (fdf->edge_len * x)
		* cos(((fdf->angle) * M_PI) / 180) - (fdf->edge_len * y)
		* sin(((fdf->angle) * M_PI) / 180), (fdf->center_y)
		+ (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180)
		+ (fdf->edge_len * y) * cos(((fdf->angle) * M_PI) / 180)
		- ((zz(fdf, y, x) * sin(M_PI / 6) * (fdf->edge_len * 2) / 255)),
		zz(fdf, y, x)};
	end = (t_point){(fdf->center_x) + (fdf->edge_len * x)
		* cos(((fdf->angle) * M_PI) / 180) - (fdf->edge_len
			* (y + 1)) * sin(((fdf->angle) * M_PI) / 180),
		(fdf->center_y) + (fdf->edge_len * x)
		* sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * (y + 1))
		* cos(((fdf->angle) * M_PI) / 180) - ((zz(fdf, y + 1, x)
				* sin(M_PI / 6) * (fdf->edge_len * 2) / 255)),
		zz(fdf, y + 1, x)};
	if ((start.x != end.x) || (start.y != end.y))
		draw_point_to_point(fdf, start, end);
}

void	formula_x_pp(t_fdf *fdf, int y, int x)
{
	t_point	start;
	t_point	end;

	start = (t_point){(fdf->center_x) + (fdf->edge_len * x)
		* cos(((fdf->angle) * M_PI) / 180) - (fdf->edge_len * y)
		* sin(((fdf->angle) * M_PI) / 180),
		(fdf->center_y) + (fdf->edge_len * x)
		* sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y)
		* cos(((fdf->angle) * M_PI) / 180) - ((zz(fdf, y, x)
				* sin(M_PI / 6) * (fdf->edge_len * 2) / 255)),
		zz(fdf, y, x)};
	end = (t_point){(fdf->center_x) + (fdf->edge_len * (x + 1))
		* cos(((fdf->angle) * M_PI) / 180) - (fdf->edge_len * y)
		* sin(((fdf->angle) * M_PI) / 180),
		(fdf->center_y) + (fdf->edge_len * (x + 1))
		* sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y)
		* cos(((fdf->angle) * M_PI) / 180) - ((zz(fdf, y, x + 1)
				* sin(M_PI / 6) * (fdf->edge_len * 2) / 255)),
		zz(fdf, y, x + 1)};
	if ((start.x != end.x) || (start.y != end.y))
		draw_point_to_point(fdf, start, end);
}
