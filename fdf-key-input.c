/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-key-input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:12:50 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/15 21:09:52 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//ft_printf("Event: Pressed key %d (ESC)\n", keysym);
int	handle_input(int keysym, t_fdf *fdf)
{
	if (keysym == 65307)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img);
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		exit(0);
	}
	else
		redraw_map(keysym, fdf);
	return (0);
}

void	redraw_map(int keysym, t_fdf *fdf)
{
	if (keysym == 114)
		color_screen(fdf, encode_rgb(255, 0, 0));
	else if (keysym == 103)
		color_screen(fdf, encode_rgb(0, 255, 0));
	else if (keysym == 98)
		color_screen(fdf, encode_rgb(0, 0, 255));
	else if (keysym == 112)
		color_screen(fdf, encode_rgb(0, 0, 0));
	else if (keysym == 109)
	{
		fdf->projection = 1;
		color_screen(fdf, 0);
	}
	else if (keysym == 121)
	{
		fdf->projection = 0;
		color_screen(fdf, 0);
	}
	else
		redraw_map_redux(keysym, fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img, 0, 0);
}

void	redraw_map_redux(int keysym, t_fdf *fdf)
{
	if (keysym == 100)
	{
		fdf->trans_x += 42;
		color_screen(fdf, 0);
	}
	else if (keysym == 97)
	{
		fdf->trans_x -= 42;
		color_screen(fdf, 0);
	}
	else if (keysym == 115)
	{
		fdf->trans_y += 42;
		color_screen(fdf, 0);
	}
	else if (keysym == 119)
	{
		fdf->trans_y -= 42;
		color_screen(fdf, 0);
	}
	else
		redraw_map_triplex(keysym, fdf);
}

void	redraw_map_triplex(int keysym, t_fdf *fdf)
{
	if (keysym == 111)
	{
		fdf->edge_len -= 1;
		if (fdf->edge_len <= 0)
			fdf->edge_len = 1;
		color_screen(fdf, 0);
	}
	else if (keysym == 59)
	{
		fdf->edge_len += 42;
		color_screen(fdf, 0);
	}
	else if (keysym == 39)
	{
		fdf->edge_len -= 42;
		if (fdf->edge_len <= 0)
			fdf->edge_len = 1;
		color_screen(fdf, 0);
	}
	else
		redraw_map_tetraplex(keysym, fdf);
}

void	redraw_map_tetraplex(int keysym, t_fdf *fdf)
{
	if (keysym == 113)
	{
		fdf->angle -= 15;
		if (fdf->angle < 0)
			fdf->angle += 360;
		ft_printf("angle: %i\n", fdf->angle);
		color_screen(fdf, 0);
	}
	else if (keysym == 101)
	{
		fdf->angle += 15;
		if (fdf->angle >= 360)
			fdf->angle = 0;
		ft_printf("angle: %i\n", fdf->angle);
		color_screen(fdf, 0);
	}
	else if (keysym == 105)
	{
		fdf->edge_len += 1;
		color_screen(fdf, 0);
	}
}
