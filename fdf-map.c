/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:54:23 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/11 14:05:45 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
