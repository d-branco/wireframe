/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:50 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 10:11:29 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> //open(), 

//	*mlx:				Connection to the graphical system
//	*win:				The window we create
//	*img:				The image we'll draw on
//	*addr:				The actual memory where we store our pixels
//	bits_per_pixel:		How many bits are used for one pixel
//	line_length:		How many bytes are used for one horizontal line
//	endian:				How the computer stores numbers in memory
typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_fdf;

//	x:	axis
//	y:	ordinate
//	z:	altitude
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;

//fdf-ininit.c
int		input_validation(int argc, char **argv);
void	initialize_mlx(t_fdf *fdf);
//fdf-close.c
int		close_window(void *param);
int		key_hook(int keycode, t_fdf *fdf);
//fdf-map.c
int		read_map(char *map_file);
int		get_map_length(char *map_file);
int		get_map_width(char *map_file);
//fdf-line.c
void	draw_point_to_point(t_fdf *img, t_point start, t_point end);

#endif
