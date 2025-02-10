/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:50 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/10 20:03:35 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> //open(), 

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;
}			t_fdf;

//fdf-input.c
int	input_validation(int argc, char **argv);
//fdf-map.c
int	read_map(char *map_file);
int	get_map_length(char *map_file);
int	get_map_width(char *map_file);

#endif
