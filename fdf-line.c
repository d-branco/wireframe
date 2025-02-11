/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:14:21 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 08:40:12 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);

//Each step is a pixel drawn
void	draw_point_to_point(t_fdf *img, t_point start, t_point end)
{
	int	max_steps;
	int	x;
	int	y;
	int	current_step;

	if (abs(end.x - start.x) >= abs(end.y - start.y))
		max_steps = abs(end.x - start.x);
	else
		max_steps = abs(end.y - start.y);
	x = start.x;
	y = start.y;
	current_step = 0;
	while (current_step <= max_steps)
	{
		my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
		x = start.x + (current_step * (end.x - start.x) / max_steps);
		y = start.y + (current_step * (end.y - start.y) / max_steps);
		current_step++;
	}
}

static void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
