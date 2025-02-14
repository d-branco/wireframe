/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:50 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/14 12:02:24 by abessa-m         ###   ########.fr       */
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
	double	angle;
}			t_fdf;

//	x:	axis
//	y:	ordinate
//	z:	altitude

#endif
