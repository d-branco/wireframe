/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:30:54 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/16 09:32:29 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 0, 0, 0xFF0000);
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if ((input_validation(argc, argv) != 1) || (read_map(argv[1]) == -1))
		exit (1);
	fdf.win_width = 1920;
	fdf.win_height = 1080 - 40;
	mlx_initialize(&fdf);
	map_initialize(&fdf, argv[1]);
	draw_center(&fdf);
	hook_n_loop(&fdf);
}
