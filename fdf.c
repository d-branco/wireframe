/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:37:00 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/10 22:23:04 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//usage
//	valgrind -s --quiet ./fdf test_maps/42.fdf
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
static int	close_window(void *param);
static void	draw_point_to_point(t_data *img, t_point start, t_point end);
int			key_hook(int keycode, t_fdf *fdf);

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if ((input_validation(argc, argv) != 1) || (read_map(argv[1]) == -1))
		return (1);
	fdf.mlx = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx, 960, 1040, "Hello ground!");
	fdf.img.img = mlx_new_image(fdf.mlx, 960, 1040);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel, 
			&fdf.img.line_length, &fdf.img.endian);
	t_point start = {42, 42, 0};
	t_point end = {225, 225, 100};
	draw_point_to_point(&fdf.img, start, end);
	start.x = 2;
	start.y = 42;
	end.x = 42;
	end.y = 2;
	draw_point_to_point(&fdf.img, start, end);
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_window, fdf.img.img, 0, 0);
	mlx_hook(fdf.mlx_window, 17, 0, close_window, &fdf);
	mlx_hook(fdf.mlx_window, 2, 1L << 0, key_hook, &fdf);
	mlx_loop(fdf.mlx);
}

static int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_window);
	exit(0);
	return (0);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_point_to_point(t_data *img, t_point start, t_point end)
{
	int	max_steps;
	int	x;
	int	y;
	int	i;

	if ((end.x - start.x) >= (end.y - start.y))
		max_steps = (end.x - start.x);
	else
		max_steps = (end.y - start.y);
	x = start.x;
	y = start.y;
	i = 1;
	while (i <= max_steps)
	{
		my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
		x = start.x + (i * (end.x - start.x) / max_steps);
		y = start.y + (i * (end.y - start.y) / max_steps);
		i++;
	}
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(fdf->mlx, fdf->mlx_window);
		exit(0);
	}
	return (0);
}
