/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:36 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/15 09:42:02 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int		handle_input(int keysym, t_fdf *fdf);
int		encode_rgb(unsigned char red, unsigned char green, unsigned char blue);
void	f(int keysym, t_fdf *fdf);
void	our_pixel_put(t_fdf *fdf, int x, int y, int color);
void	color_screen(t_fdf *fdf, int color);
int		close_window(void *param);
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
int		paint_zz(int green);
void	draw_center(t_fdf *fdf);
void	draw_point_to_point(t_fdf *fdf, t_point start, t_point end);
void	draw_map(t_fdf *fdf);
void	draw_lines_paralel_projection(t_fdf *fdf, int y, int x);
int		zz(t_fdf *fdf, int y, int x);
void	projection_paralel(t_fdf *fdf);
void	projection_isometric(t_fdf *fdf);
void	draw__lines_isometric_projection(t_fdf *fdf, int y, int x);

//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 0, 0, 0xFF0000);
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if ((input_validation(argc, argv) != 1) || (read_map(argv[1]) == -1))
		exit (1);
	fdf.win_width = 1920;// / 2;
	fdf.win_height = 1080 - 40;
	mlx_initialize(&fdf);
	map_initialize(&fdf, argv[1]);
	draw_center(&fdf);
	hook_n_loop(&fdf);
}

void	draw_map(t_fdf *fdf)
{
	projection_isometric(fdf);
	//projection_paralel(fdf);
}

void	projection_isometric(t_fdf *fdf)
{
	int	y;
	int	x;

	fdf->center_x = fdf->trans_x + (fdf->win_width / 2);
	fdf->center_y = fdf->trans_y + (fdf->win_height / 2);
	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			draw__lines_isometric_projection(fdf, y, x);
			x++;
		}
		y++;
	}
}

void	draw__lines_isometric_projection(t_fdf *fdf, int y, int x)
{
	t_point	start;
	t_point	end;

	if (x < fdf->map_length - 1)
	{
		start = (t_point){
			(fdf->center_x) + (fdf->edge_len * x) * cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * sin(((fdf->angle + 30) * M_PI) / 180),
			(fdf->center_y) - (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * cos(((fdf->angle + 30) * M_PI) / 180) - (zz(fdf, y, x) / 8),
			zz(fdf, y, x)};
		end = (t_point){
			(fdf->center_x) + (fdf->edge_len * (x + 1)) * cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * sin(((fdf->angle + 30) * M_PI) / 180),
			(fdf->center_y) - (fdf->edge_len * (x + 1)) * sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * cos(((fdf->angle + 30) * M_PI) / 180) - (zz(fdf, y, x + 1) / 8),
			zz(fdf, y, x + 1)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
	if (y < fdf->map_width - 1)
	{
		start = (t_point){
			(fdf->center_x) + (fdf->edge_len * x) * cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * sin(((fdf->angle + 30) * M_PI) / 180),
			(fdf->center_y) - (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * cos(((fdf->angle + 30) * M_PI) / 180) - (zz(fdf, y, x) / 8),
			zz(fdf, y, x)};
		end = (t_point){
			(fdf->center_x) + (fdf->edge_len * x) * cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * (y + 1)) * sin(((fdf->angle + 30) * M_PI) / 180),
			(fdf->center_y) - (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * (y + 1)) * cos(((fdf->angle + 30) * M_PI) / 180) - (zz(fdf, y + 1, x) / 8),
			zz(fdf, y + 1, x)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
}

void	projection_paralel(t_fdf *fdf)
{
	
	int	y;
	int	x;

	fdf->center_x = fdf->trans_x + (fdf->win_width / 2)
		- ((fdf->edge_len * fdf->map_length / 2)
			* cos(((fdf->angle) * M_PI) / 180)
			+ (fdf->edge_len * fdf->map_width / 2)
			* sin(((fdf->angle) * M_PI) / 180));
	fdf->center_y = fdf->trans_y + (fdf->win_height / 2)
		- (-(fdf->edge_len * fdf->map_length / 2)
			* sin(((fdf->angle) * M_PI) / 180)
			+ (fdf->edge_len * fdf->map_width / 2)
			* cos(((fdf->angle) * M_PI) / 180));
	y = 0;
	while (y < fdf->map_width)
	{
		x = 0;
		while (x < fdf->map_length)
		{
			draw_lines_paralel_projection(fdf, y, x);
			x++;
		}
		y++;
	}
}

//ft_printf("Start    x: %i,    y: %i,    z: %i\n", start.x, start.y, start.z);
//ft_printf("End      x: %i,    y: %i,    z: %i\n", end.x, end.y, end.z);
void	draw_lines_paralel_projection(t_fdf *fdf, int y, int x)
{
	t_point	start;
	t_point	end;

	if (x < fdf->map_length - 1)
	{
		start = (t_point){(fdf->center_x) + (fdf->edge_len * x)
			* cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y)
			* sin(((fdf->angle) * M_PI) / 180), (fdf->center_y) - (fdf->edge_len
				* x) * sin(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y)
			* cos(((fdf->angle) * M_PI) / 180) - (zz(fdf, y, x) / 8),
			zz(fdf, y, x)};
		end = (t_point){(fdf->center_x) + (fdf->edge_len * (x + 1)) * cos(((
						fdf->angle) * M_PI) / 180) + (fdf->edge_len * y) * sin((
					(fdf->angle) * M_PI) / 180), (fdf->center_y)
		- (fdf->edge_len * (x + 1)) * sin(((fdf->angle) * M_PI) / 180)
		+ (fdf->edge_len * y) * cos(((fdf->angle) * M_PI) / 180) - (
				zz(fdf, y, x + 1) / 8), zz(fdf, y, x + 1)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
	if (y < fdf->map_width - 1)
	{
		start = (t_point){(fdf->center_x) + (fdf->edge_len * x)
			* cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * y)
			* sin(((fdf->angle) * M_PI) / 180), (fdf->center_y)
			- (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180)
			+ (fdf->edge_len * y) * cos(((fdf->angle) * M_PI) / 180)
			- (zz(fdf, y, x) / 8), zz(fdf, y, x)};
		end = (t_point){(fdf->center_x) + (fdf->edge_len * x)
			* cos(((fdf->angle) * M_PI) / 180) + (fdf->edge_len * (y + 1))
			* sin(((fdf->angle) * M_PI) / 180), (fdf->center_y)
			- (fdf->edge_len * x) * sin(((fdf->angle) * M_PI) / 180)
			+ (fdf->edge_len * (y + 1)) * cos(((fdf->angle) * M_PI) / 180)
			- (zz(fdf, y + 1, x) / 8), zz(fdf, y + 1, x)};
		if ((start.x != end.x) || (start.y != end.y))
			draw_point_to_point(fdf, start, end);
	}
}

// linear interpolation
int	zz(t_fdf *fdf, int y, int x)
{
	int	zz;

	zz = ((fdf->map[y][x] - fdf->map_lowest) * 255)
		/ (fdf->map_highest - fdf->map_lowest);
	if (zz < 0)
		zz = 0;
	if (zz > 255)
		zz = 255;
	return (zz);
}

void	draw_center(t_fdf *fdf)
{
	t_point	start;
	t_point	end;

	start = (t_point)
	{(int)((fdf->win_width / 2) - 5), (int)(fdf->win_height / 2), 0};
	end = (t_point)
	{(int)((fdf->win_width / 2) + 5 + 1), (int)(fdf->win_height / 2), 0};
	draw_point_to_point(fdf, start, end);
	start = (t_point)
	{(int)(fdf->win_width / 2), (int)((fdf->win_height / 2) - 5), 0};
	end = (t_point)
	{(int)(fdf->win_width / 2), (int)((fdf->win_height / 2) + 5 + 1), 0};
	draw_point_to_point(fdf, start, end);
	ft_printf("Center point at "
		"x: %i    y: %i\n", (fdf->win_width / 2), (fdf->win_height / 2));
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img, 0, 0);
	return ;
}

/*typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;*/
void	draw_point_to_point(t_fdf *fdf, t_point start, t_point end)
{
	int		max_steps;
	double	x;
	double	y;
	int		z;
	int		current_step;

	if (abs(end.x - start.x) >= abs(end.y - start.y))
		max_steps = abs(end.x - start.x);
	else
		max_steps = abs(end.y - start.y);
	x = start.x;
	y = start.y;
	z = paint_zz(start.z);
	current_step = 0;
	while (current_step <= max_steps)
	{
		our_pixel_put(fdf, x, y, z);
		x = start.x + (current_step * (end.x - start.x) / max_steps);
		y = start.y + (current_step * (end.y - start.y) / max_steps);
		z = paint_zz(start.z + (current_step * (end.z - start.z) / max_steps));
		current_step++;
	}
}

int	paint_zz(int green)
{
	int	red;
	int	blue;

	if (green < 0)
		green = 0;
	if (green > 255)
		green = 255;
	green = green / 2 + 127;
	red = 255 - green;
	green = green;
	blue = 255 - green;
	return ((red << 16) | (green << 8) | blue);
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
	fdf->angle = 30; // 30 to start in isometric
	fdf->edge_len = 20; //40 works well for 42. Needs to be calculated
	fdf->center_x = fdf->win_width / 2;
	fdf->center_y = fdf->win_height / 2;
	fdf->trans_x = 0;
	fdf->trans_y = 0;
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
		ft_printf("Event: Pressed key %d (ESC)\n", keysym);//
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
	ft_printf("Event: Pressed key %d\n", keysym);//
	if (keysym == 113)
	{
		fdf->angle -= 15;
		if (fdf->angle < 0)
			fdf->angle += 360;
		ft_printf("angle: %i\n", fdf->angle);
		color_screen(fdf, 0);
	}
	if (keysym == 114)
		color_screen(fdf, encode_rgb(255, 0, 0));
	if (keysym == 103)
		color_screen(fdf, encode_rgb(0, 255, 0));
	if (keysym == 98)
		color_screen(fdf, encode_rgb(0, 0, 255));
	if (keysym == 112)
		color_screen(fdf, encode_rgb(0, 0, 0));
	if (keysym == 100)
	{
		fdf->trans_x += 42;
		color_screen(fdf, 0);
	}
	if (keysym == 97)
	{
		fdf->trans_x -= 42;
		color_screen(fdf, 0);
	}
	if (keysym == 115)
	{
		fdf->trans_y += 42;
		color_screen(fdf, 0);
	}
	if (keysym == 119)
	{
		fdf->trans_y -= 42;
		color_screen(fdf, 0);
	}
	if (keysym == 101)
	{
		fdf->angle += 15;
		if (fdf->angle >= 360)
			fdf->angle = 0;
		ft_printf("angle: %i\n", fdf->angle);
		color_screen(fdf, 0);
	}
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img, 0, 0);
}

void	our_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int	offset;

	if ((x < 0) || (x >= fdf->win_width) || (y < 0) | (y >= fdf->win_height))
		return ;
	offset = (fdf->line_length * y) + (x * (fdf->bits_per_pixel / 8));
	*((unsigned int *)(fdf->addr + offset)) = color;
}
