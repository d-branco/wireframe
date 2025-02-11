/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:14:21 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 10:13:15 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
static unsigned int	paint_g(int green);

//Each step is a pixel drawn
void	draw_point_to_point(t_fdf *img, t_point start, t_point end)
{
	int	max_steps;
	int	x;
	int	y;
	int	z;
	int	current_step;

	if (abs(end.x - start.x) >= abs(end.y - start.y))
		max_steps = abs(end.x - start.x);
	else
		max_steps = abs(end.y - start.y);
	x = start.x;
	y = start.y;
	z = paint_g(start.z);
	current_step = 0;
	while (current_step <= max_steps)
	{
		my_mlx_pixel_put(img, x, y, z);
		x = start.x + (current_step * (end.x - start.x) / max_steps);
		y = start.y + (current_step * (end.y - start.y) / max_steps);
		z = paint_g(start.z + (current_step * (end.z - start.z) / max_steps));
		current_step++;
	}
}

static void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static unsigned int	paint_g(int green)
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
	return (255 << 24 | (red << 16) | (green << 8) | blue);
}
