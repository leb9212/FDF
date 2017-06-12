/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:45:32 by elee              #+#    #+#             */
/*   Updated: 2016/11/24 18:54:42 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

void	zoom(t_fdf *fdf, t_point *point)
{
	(*point).x = fdf->wcentx - (fdf->xmax / 2 - (*point).x) * fdf->step;
	(*point).y = fdf->wcenty - (fdf->ymax / 2 - (*point).y) * fdf->step;
	(*point).z *= fdf->step;
}

void	translate(t_fdf *fdf, t_point *point)
{
	(*point).x += fdf->tranx * fdf->step;
	(*point).y += fdf->trany * fdf->step;
}

void	rotate(t_fdf *fdf, t_point *point)
{
	double a;
	double x;
	double y;
	double z;

	a = (DEG * M_PI) / 180.0;
	x = rint(((*point).x - fdf->wcentx) * cos(a * fdf->roty)
			- ((*point).z) * sin(a * fdf->roty) + fdf->wcentx);
	z = rint(((*point).x - fdf->wcentx) * sin(a * fdf->roty)
			+ ((*point).z) * cos(a * fdf->roty));
	(*point).x = x;
	y = rint(((*point).y - fdf->wcenty) * cos(a * fdf->rotx)
			- z * sin(a * fdf->rotx) + fdf->wcenty);
	(*point).y = y;
	x = rint(((*point).x - fdf->wcentx) * cos(a * fdf->rotz)
			- ((*point).y - fdf->wcenty) * sin(a * fdf->rotz) + fdf->wcentx);
	y = rint(((*point).x - fdf->wcentx) * sin(a * fdf->rotz)
			+ ((*point).y - fdf->wcenty) * cos(a * fdf->rotz) + fdf->wcenty);
	(*point).x = x;
	(*point).y = y;
}
