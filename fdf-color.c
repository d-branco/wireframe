/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:20:21 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/16 17:02:44 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	our_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int	offset;

	if ((x < 0) || (x >= fdf->win_width) || (y < 0) | (y >= fdf->win_height))
		return ;
	offset = (fdf->line_length * y) + (x * (fdf->bits_per_pixel / 8));
	*((unsigned int *)(fdf->addr + offset)) = color;
}

int	encode_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void	color_screen(t_fdf *fdf, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->win_height)
	{
		x = 0;
		while (x < fdf->win_width)
		{
			our_pixel_put(fdf, x, y, color);
			x++;
		}
		y++;
	}
}

// linear interpolation
int	zz(t_fdf *fdf, int y, int x)
{
	int	zz;
	int	denominator;

	denominator = fdf->map_highest - fdf->map_lowest;
	if (denominator == 0)
		return (0);
	zz = ((fdf->map[y][x] - fdf->map_lowest) * 255) / denominator;
	if (zz < 0)
		zz = 0;
	if (zz > 255)
		zz = 255;
	return (zz);
}
