/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:36 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/14 16:09:38 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int		handle_input(int keysym, t_fdf *fdf);
int		encode_rgb(unsigned char red, unsigned char green, unsigned char blue);
void	f(int keysym, t_fdf *fdf);
void	our_pixel_put(t_fdf *fdf, int x, int y, int color);
int		close_window(void *param);
int		key_hook(int keycode, t_fdf *fdf);
void	mlx_initialize(t_fdf *fdf);
void	hook_n_loop(t_fdf *fdf);
int		input_validation(int argc, char **argv);
int		validate_map_name(char **argv);
void	map_the_map(t_fdf *fdf, char *map_file);
void	map_the_peaks(t_fdf *fdf);
void	map_initialize(t_fdf *fdf, char *map_name);
int		read_map(char *map_file);
int		get_map_length(char *map_file);
int		get_map_width(char *map_file);

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
	hook_n_loop(&fdf);
}

int	read_map(char *map_file)
{
	char	*line;
	int		map_file_fd;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	if (map_file_fd == -1)
		return (ft_printf("Error openning the map file!\n"), -1);
	line = get_next_line(map_file_fd);
	if (!line)
		return (ft_printf("Error reading map file!\n"), 1);
	while (line)
	{
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	ft_printf("Map size is %i times %i\n", get_map_length(map_file),
		get_map_width(map_file));
	return (0);
}

int	get_map_length(char *map_file)
{
	char	*line;
	int		map_file_fd;
	int		length;
	char	**splitted_line;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	if (map_file_fd == -1)
		return (ft_printf("Error openning the map file!\n"), -1);
	line = get_next_line(map_file_fd);
	if (!line)
		return (ft_printf("Error reading map file!\n"), 1);
	splitted_line = ft_split(line, ' ');
	length = 0;
	while (splitted_line[length] && (splitted_line[length][0] != '\n'))
		length++;
	free_splitted(splitted_line);
	while (line)
	{
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	return (length);
}

int	get_map_width(char *map_file)
{
	char	*line;
	int		map_file_fd;
	int		width;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	if (map_file_fd == -1)
		return (ft_printf("Error openning the map file!\n"), -1);
	line = get_next_line(map_file_fd);
	if (!line)
		return (ft_printf("Error reading map file!\n"), 1);
	width = 0;
	while (line)
	{
		width++;
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	return (width);
}

void	map_initialize(t_fdf *fdf, char *map_name)
{
	int	i;

	fdf->map = NULL;
	fdf->map_width = get_map_width(map_name);
	fdf->map_length = get_map_length(map_name);
	fdf->map = (int **) ft_calloc(fdf->map_width, sizeof(int *));
	i = 0;
	while (i < fdf->map_width)
	{
		fdf->map[i] = (int *) ft_calloc(fdf->map_length, sizeof(int));
		if (fdf->map[i] == NULL)
		{
			ft_printf("Error allocating map!\n");
			exit (5);
		}
		i++;
	}
	map_the_map(fdf, map_name);
	map_the_peaks(fdf);
	fdf->angle = 0;
}

void	map_the_map(t_fdf *fdf, char *map_file)
{
	int		x;
	int		y;
	char	*line;
	char	**splitted_line;
	int		map_file_fd;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	line = get_next_line(map_file_fd);
	y = -1;
	while (++y < fdf->map_width)
	{
		x = 0;
		splitted_line = ft_split(line, ' ');
		while (x < fdf->map_length)
		{
			fdf->map[y][x] = ft_atoi(splitted_line[x]);
			x++;
		}
		free_splitted(splitted_line);
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	return ;
}

void	map_the_peaks(t_fdf *fdf)
{
	int	y;
	int	x;

	fdf->map_highest = fdf->map[0][0];
	fdf->map_lowest = fdf->map[0][0];
	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			if (fdf->map[y][x] < fdf->map_lowest)
				fdf->map_lowest = fdf->map[y][x];
			if (fdf->map[y][x] > fdf->map_highest)
				fdf->map_highest = fdf->map[y][x];
			x++;
		}
		y++;
	}
	ft_printf("Maps highest peak: %i\n", fdf->map_highest);
	ft_printf("Maps lowest peak: %i\n", fdf->map_lowest);
}

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

int	validate_map_name(char **argv)
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

void	hook_n_loop(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx_window, handle_input, fdf);
	mlx_hook(fdf->mlx_window, 17, 0, close_window, fdf);
	mlx_hook(fdf->mlx_window, 2, 1L << 0, key_hook, fdf);
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

int	key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == 32)
	{
		fdf->angle++;
		if (fdf->angle >= 360)
			fdf->angle = 0;
		ft_printf("angle: %i\n", fdf->angle);
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

//ft_printf("Event: Pressed key %d\n", keysym);
int	handle_input(int keysym, t_fdf *fdf)
{
	if (keysym == 65307)
	{
		ft_printf("Event: Pressed key %d (ESC)\n", keysym);
		mlx_destroy_image(fdf->mlx_ptr, fdf->img);
		mlx_destroy_window(fdf->mlx_ptr, fdf->mlx_window);
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		exit(0);
	}
	else
		f(keysym, fdf);
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
	while (y < fdf->win_height)
	{
		x = 0;
		while (x < fdf->win_width)
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
