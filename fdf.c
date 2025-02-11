/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:37:00 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 08:39:11 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//usage
//	make re && make clean && valgrind -s --quiet ./fdf test_maps/42.fdf

//typedef struct	s_fdf
//{
//	void	*mlx;
//	void	*mlx_window;
//	void	*img;
//	char	*addr;
//	int		bits_per_pixel;
//	int		line_length;
//	int		endian;
//}			t_fdf;

//typedef struct s_point
//{
//	int		x;
//	int		y;
//	int		z;
//}			t_point;

static void	draw_cross(t_fdf *fdf);

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if ((input_validation(argc, argv) != 1) || (read_map(argv[1]) == -1))
		return (1);
	
	initialize_mlx(&fdf);

	draw_cross(&fdf);
	
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_window, fdf.img, 0, 0);
	mlx_hook(fdf.mlx_window, 17, 0, close_window, &fdf);
	mlx_hook(fdf.mlx_window, 2, 1L << 0, key_hook, &fdf);
	mlx_loop(fdf.mlx);
}

static void	draw_cross(t_fdf *fdf)
{
	t_point start;
	t_point end;

	start = (t_point){200, 100};
	end = (t_point){300, 100};
	draw_point_to_point(fdf, start, end);
	start = (t_point){300, 100};
	end = (t_point){300, 200};
	draw_point_to_point(fdf, start, end);
	start = (t_point){300, 200};
	end = (t_point){400, 200};
	draw_point_to_point(fdf, start, end);
	start = (t_point){400, 200};
	end = (t_point){400, 300};
	draw_point_to_point(fdf, start, end);
	start = (t_point){400, 300};
	end = (t_point){300, 300};
	draw_point_to_point(fdf, start, end);
	start = (t_point){300, 300};
	end = (t_point){300, 500};
	draw_point_to_point(fdf, start, end);
	start = (t_point){300, 500};
	end = (t_point){200, 500};
	draw_point_to_point(fdf, start, end);
	start = (t_point){200, 500};
	end = (t_point){200, 300};
	draw_point_to_point(fdf, start, end);
	start = (t_point){200, 300};
	end = (t_point){100, 300};
	draw_point_to_point(fdf, start, end);
	start = (t_point){100, 300};
	end = (t_point){100, 200};
	draw_point_to_point(fdf, start, end);
	start = (t_point){100, 200};
	end = (t_point){200, 200};
	draw_point_to_point(fdf, start, end);
	start = (t_point){200, 200};
	end = (t_point){200, 100};
	draw_point_to_point(fdf, start, end);
}