/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:31:27 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/16 09:32:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> //open(), 

// Graphic library
//	*mlx:			Connection to the graphical system
// Window specific
//	*win:			The window we create
// Image specific
//	*img:			The image we'll draw on
//	*addr:			The actual memory where we store our pixels
//	bits_per_pixel:	How many bits are used for one pixel
//	line_length:	How many bytes are used for one horizontal line
//	endian:			How the computer stores numbers in memory
typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_width;
	int		win_height;
	int		map_length;
	int		map_width;
	int		**map;
	int		map_highest;
	int		map_lowest;
	int		angle;
	int		edge_len;
	int		center_x;
	int		center_y;
	int		trans_x;
	int		trans_y;
	int		projection;
}			t_fdf;

//	x:	axis
//	y:	ordinate
//	z:	altitude
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}			t_point;

//fdf-key-input.c
int		handle_input(int keysym, t_fdf *fdf);
void	redraw_map(int keysym, t_fdf *fdf);
void	redraw_map_redux(int keysym, t_fdf *fdf);
void	redraw_map_triplex(int keysym, t_fdf *fdf);
void	redraw_map_tetraplex(int keysym, t_fdf *fdf);
//fdf-init-validation.c
int		input_validation(int argc, char **argv);
int		validate_map_name(char **argv);
int		read_map(char *map_file);
int		get_map_length(char *map_file);
int		get_map_width(char *map_file);
//fdf-init-map.c
void	map_the_map(t_fdf *fdf, char *map_file);
void	map_the_peaks(t_fdf *fdf);
void	map_initialize(t_fdf *fdf, char *map_name);
void	fit_map(t_fdf *fdf);
//fdf-color.c
void	our_pixel_put(t_fdf *fdf, int x, int y, int color);
int		encode_rgb(unsigned char red, unsigned char green, unsigned char blue);
void	color_screen(t_fdf *fdf, int color);
int		zz(t_fdf *fdf, int y, int x);

//fdf-window.c
void	hook_n_loop(t_fdf *fdf);
int		close_window(void *param);
void	mlx_initialize(t_fdf *fdf);
//fdf-draw.c
void	draw_center(t_fdf *fdf);
void	draw_point_to_point(t_fdf *fdf, t_point start, t_point end);
void	draw_map(t_fdf *fdf);
int		paint_zz(int green);

//fdf-military.c
void	draw_lines_paralel_projection(t_fdf *fdf, int y, int x);
void	projection_paralel(t_fdf *fdf);
void	formula_x_pp(t_fdf *fdf, int y, int x);
void	formula_y_pp(t_fdf *fdf, int y, int x);

//fdf-isometric.c
void	projection_isometric(t_fdf *fdf);
void	draw__lines_isometric_projection(t_fdf *fdf, int y, int x);
void	formula_x_ip(t_fdf *fdf, int y, int x);
void	formula_y_ip(t_fdf *fdf, int y, int x);

#endif
