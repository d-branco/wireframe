/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:32:57 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/16 09:33:01 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
//t_point	start;
//t_point	end;
//
//start = (t_point)
//{(int)((fdf->win_width / 2) - 5), (int)(fdf->win_height / 2), 0};
//end = (t_point)
//{(int)((fdf->win_width / 2) + 5 + 1), (int)(fdf->win_height / 2), 0};
//draw_point_to_point(fdf, start, end);
//start = (t_point)
//{(int)(fdf->win_width / 2), (int)((fdf->win_height / 2) - 5), 0};
//end = (t_point)
//{(int)(fdf->win_width / 2), (int)((fdf->win_height / 2) + 5 + 1), 0};
//draw_point_to_point(fdf, start, end);
//ft_printf("Center point at "
//	"x: %i    y: %i\n", (fdf->win_width / 2), (fdf->win_height / 2));
*/
void	draw_center(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img, 0, 0);
	return ;
}

void	draw_map(t_fdf *fdf)
{
	if (fdf->projection == 0)
		projection_isometric(fdf);
	else if (fdf->projection == 1)
		projection_paralel(fdf);
}

/*typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;*/
void	draw_point_to_point(t_fdf *fdf, t_point start, t_point end)
{
	int		max_steps;
	double	x;
	double	y;
	int		z;
	int		current_step;

	if (abs(end.x - start.x) >= abs(end.y - start.y))
		max_steps = abs(end.x - start.x);
	else
		max_steps = abs(end.y - start.y);
	x = start.x;
	y = start.y;
	z = paint_zz(start.z);
	current_step = 0;
	while (current_step <= max_steps)
	{
		our_pixel_put(fdf, x, y, z);
		x = start.x + (current_step * (end.x - start.x) / max_steps);
		y = start.y + (current_step * (end.y - start.y) / max_steps);
		z = paint_zz(start.z + (current_step * (end.z - start.z) / max_steps));
		current_step++;
	}
}

int	paint_zz(int green)
{
	int	red;
	int	blue;

	if (green < 0)
		green = 0;
	if (green > 255)
		green = 255;
	green = green / 2 + 127;
	red = 255 - green;
	green = green;
	blue = 255 - green;
	return ((red << 16) | (green << 8) | blue);
}
