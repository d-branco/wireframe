/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p-draw_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:49:06 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/10 17:37:08 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
static int	close_window(void *param);

	//int offset = (y * line_length + x * (bits_per_pixel / 8));
int	main(void)
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Hello ground!");
	img.img = mlx_new_image(mlx, 1920, 1820);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_hook(mlx_window, 17, 0, close_window, NULL);
	mlx_loop(mlx);
}

static int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
