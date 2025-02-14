/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:36 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/14 12:10:42 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#define WIDTH	225
#define HEIGHT	225

int		handle_input(int keysym, t_fdf *fdf);
int		encode_rgb(unsigned char red, unsigned char green, unsigned char blue);
void	f(int keysym, t_fdf *fdf);
void	our_pixel_put(t_fdf *fdf, int x, int y, int color);
int		close_window(void *param);
int		key_hook(int keycode, t_fdf *fdf);

/*typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_fdf;
*/

int	main(void)
{
	t_fdf	fdf;

	fdf.mlx_ptr = mlx_init();
	if (NULL == fdf.mlx_ptr)
		return (1);
	fdf.mlx_window = mlx_new_window(fdf.mlx_ptr, HEIGHT, WIDTH, "Here I am");
	if (fdf.mlx_window == NULL)
	{
		mlx_destroy_display(fdf.mlx_ptr);
		free(fdf.mlx_ptr);
		return (2);
	}
	fdf.img = mlx_new_image(fdf.mlx_ptr, WIDTH, HEIGHT);
	if (fdf.img == NULL)
	{
		mlx_destroy_window(fdf.mlx_ptr, fdf.mlx_window);
		mlx_destroy_display(fdf.mlx_ptr);
		free(fdf.mlx_ptr);
		return (3);
	}
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, &fdf.line_length, &fdf.endian);
	if (fdf.addr == NULL)
	{
		mlx_destroy_image(fdf.mlx_ptr, fdf.img);
		mlx_destroy_window(fdf.mlx_ptr, fdf.mlx_window);
		mlx_destroy_display(fdf.mlx_ptr);
		free(fdf.mlx_ptr);
		return (3);
	}
	ft_printf("IMG: Line length: %i\nIMG: bits per pixel: %i\nIMG: endian: %i\n", fdf.line_length, fdf.bits_per_pixel, fdf.endian);
	mlx_key_hook(fdf.mlx_window, handle_input, &fdf);
	mlx_hook(fdf.mlx_window, 17, 0, close_window, &fdf);
	mlx_hook(fdf.mlx_window, 2, 1L << 0, key_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
}

int	key_hook(int keycode, t_fdf *fdf)
	{
		if (keycode == 32)
		{
			fdf->angle += (M_PI * 2) / 360;
			if (fdf->angle > (M_PI * 2))
				fdf->angle = 0;
		}
		return (0);
	}

int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img);
	mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
	free(fdf->mlx_ptr);
	exit(0);
}

int	handle_input(int keysym, t_fdf *fdf)
{
	if (keysym == 65307)
	{
		ft_printf("Event: Pressed key %d\n", keysym);
		mlx_destroy_image(fdf->mlx_ptr, fdf->img);
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		exit(0);
	}
	else
		f(keysym, fdf);
	ft_printf("Event: Pressed key %d\n", keysym);
	return (0);
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
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			our_pixel_put(fdf, x, y, color);
			x++;
		}
		y++;
	}
}

void	f(int keysym, t_fdf *fdf)
{
	if (keysym == 114)
		color_screen(fdf, encode_rgb(255, 0, 0));
	if (keysym == 103)
		color_screen(fdf, encode_rgb(0, 255, 0));
	if (keysym == 98)
		color_screen(fdf, encode_rgb(0, 0, 255));
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img, 0, 0);
}

void	our_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int	offset;

	offset = (fdf->line_length * y) + (x * (fdf->bits_per_pixel / 8));
	*((unsigned int *)(fdf->addr + offset)) = color;
}
