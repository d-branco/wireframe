/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:37:00 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/10 16:13:52 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

	//int offset = (y * line_length + x * (bits_per_pixel / 8));

//usage
//	valgrind -s --quiet ./fdf test_maps/42.fdf

int	main(int argc, char **argv)
{
	if ((input_validation(argc, argv) != 1) || (read_map(argv[1]) == -1))
		return (1);
}
