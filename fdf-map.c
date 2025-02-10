/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf-map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:54:23 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/10 13:45:02 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(char *map_file, int **map)
{
	char	*line;
	int		map_file_fd;

	map_file_fd = open(map_file, O_RDONLY, 0644);
	if (map_file_fd == -1)
		return (-1);
	line = get_next_line(map_file_fd);
	if (!line)
		return (ft_printf("Error reading map file!\n"), 1);
	while (line)
	{
		ft_putstr_fd(line, 1); //remove
		free(line);
		line = get_next_line(map_file_fd);
	}
	free(line);
	close(map_file_fd);
	return (0);
}
