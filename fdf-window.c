/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:20:36 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/15 21:32:34 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook_n_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx_window, handle_input, fdf);
	mlx_hook(fdf->mlx_window, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx_ptr);
}

void	mlx_initialize(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (NULL == fdf->mlx_ptr)
		exit (1);
	fdf->mlx_window = mlx_new_window(
			fdf->mlx_ptr, fdf->win_width, fdf->win_height, "Here I am");
	if (fdf->mlx_window == NULL)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		exit (2);
	}
	fdf->img = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height);
	if (fdf->img == NULL)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		exit (3);
	}
	fdf->addr = mlx_get_data_addr(
			fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
}

int	close_window(void *param)
{
	t_fdf	*fdf;
	int		i;

	fdf = (t_fdf *)param;
	i = 0;
	while (i < fdf->map_width)
		free(fdf->map[i++]);
	free(fdf->map);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img);
	mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
	exit(0);
}
