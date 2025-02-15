/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-init-validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:20:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/15 21:29:21 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
