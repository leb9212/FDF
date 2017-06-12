/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:30:06 by elee              #+#    #+#             */
/*   Updated: 2016/11/24 19:16:47 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

t_point	**array_copy(t_fdf *fdf)
{
	t_point	**new;
	int		i;
	int		j;

	new = (t_point**)malloc(sizeof(t_point*) * fdf->ymax);
	j = -1;
	while (++j < fdf->ymax)
	{
		new[j] = (t_point*)malloc(sizeof(t_point) * fdf->xmax);
		i = -1;
		while (++i < fdf->xmax)
			new[j][i] = fdf->map[j][i];
	}
	return (new);
}

void	array_destroy(t_fdf *fdf, t_point **map)
{
	int		j;

	j = -1;
	while (++j < fdf->ymax)
		free(map[j]);
	free(map);
}

void	array_iter(t_fdf *fdf, t_point **map, void f(t_fdf*, t_point*))
{
	int		i;
	int		j;

	j = -1;
	while (++j < fdf->ymax)
	{
		i = -1;
		while (++i < fdf->xmax)
			f(fdf, &map[j][i]);
	}
}

void	array_minmax(t_fdf *fdf, t_point **map, int minmax[2])
{
	int		i;
	int		j;

	minmax[0] = INT_MAX;
	minmax[1] = INT_MIN;
	j = -1;
	while (++j < fdf->ymax)
	{
		i = -1;
		while (++i < fdf->xmax)
		{
			minmax[0] = (map[j][i].z < minmax[0]) ? map[j][i].z : minmax[0];
			minmax[1] = (map[j][i].z > minmax[1]) ? map[j][i].z : minmax[1];
		}
	}
}
