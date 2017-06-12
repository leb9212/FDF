/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:46:37 by elee              #+#    #+#             */
/*   Updated: 2016/11/25 16:37:47 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

void	handle_error(t_fdf *fdf, int file, int fd)
{
	(fdf->map) ? array_destroy(fdf, fdf->map) : 0;
	(file) ? close(fd) : 0;
	(fdf) ? free(fdf) : 0;
	exit(0);
}

void	read_map_size(char *file, t_fdf *fdf)
{
	int		fd;
	int		count;
	char	*line;
	char	**coords;

	if ((fd = open(file, O_RDONLY)) == -1 && ft_printf("error\n"))
		handle_error(fdf, 0, 0);
	while (get_next_line(fd, &line) > 0 && ++(fdf->ymax))
	{
		coords = ft_strsplit(line, ' ');
		count = ft_ptrlen(coords);
		(fdf->ymax == 1) ? fdf->xmax = count : 0;
		ft_free_two(coords);
		free(line);
		if (count != fdf->xmax && ft_printf("error\n"))
			handle_error(fdf, 1, fd);
	}
	close(fd);
	fdf->step = MIN(XSIZE * 0.75 / fdf->xmax, YSIZE * 0.75 / fdf->ymax);
	fdf->step += (fdf->step == 0) ? 1 : 0;
}

void	read_map(char *file, t_fdf *fdf)
{
	int		fd;
	int		x;
	int		y;
	char	*line;
	char	**coords;

	if ((fd = open(file, O_RDONLY)) == -1 && ft_printf("error\n"))
		handle_error(fdf, 0, 0);
	fdf->map = (t_point**)malloc(sizeof(t_point*) * fdf->ymax);
	y = -1;
	while (get_next_line(fd, &line) > 0 && ++y >= 0)
	{
		fdf->map[y] = (t_point*)malloc(sizeof(t_point) * fdf->xmax);
		coords = ft_strsplit(line, ' ');
		x = -1;
		while (coords[++x])
		{
			fdf->map[y][x].x = x;
			fdf->map[y][x].y = y;
			fdf->map[y][x].z = ft_atoi(coords[x]);
		}
		ft_free_two(coords);
		free(line);
	}
	close(fd);
}
