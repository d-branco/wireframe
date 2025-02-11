/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:11:42 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 08:12:38 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	validate_map_name(char **argv);

int	input_validation(int argc, char **argv)
{
	int	result;

	result = 1;
	if (argc != 2)
	{
		if (argc == 1)
			ft_printf("No map file  provided!\n");
		if (argc > 2)
			ft_printf("Too many arguments!\n");
		result = 0;
	}
	else
		result = validate_map_name(argv);
	return (result);
}

static int	validate_map_name(char **argv)
{
	int	result;
	int	len;

	result = 1;
	len = ft_strlen(argv[1]);
	if (len <= 4)
	{
		ft_printf("Invalid map file!\n");
		result = 0;
	}
	else if ((argv[1][len - 4] != '.') || (argv[1][len - 3] != 'f')
		|| (argv[1][len - 2] != 'd') || (argv[1][len - 1] != 'f'))
	{
		ft_printf("Invalid map file!\n");
		result = 0;
	}
	if (result == 0)
		ft_printf("usage:\n./fdf <map_name>.fdf\n");
	return (result);
}


void	initialize_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->mlx_window = mlx_new_window(fdf->mlx, 960, 1040, "Hello ground!");
	fdf->img = mlx_new_image(fdf->mlx, 960, 1040);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, 
			&fdf->line_length, &fdf->endian);
}
