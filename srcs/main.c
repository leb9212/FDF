/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:27:24 by elee              #+#    #+#             */
/*   Updated: 2016/12/30 22:07:00 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

static int	ft_strtorgb(char *s, int c[3])
{
	int		index;

	index = -1;
	while (++index < 3)
		c[index] = 0;
	s = ft_strupcase(s);
	if (ft_strlen(s) != 8 || ft_strncmp(s, "0X", 2))
		return (0);
	s += 2;
	index = -1;
	while (s[++index])
		if (!ft_isxdigit(s[index]))
			return (0);
	c[0] = (ft_isdigit(s[0])) ? 16 * (s[0] - '0') : 16 * (s[0] - 'A' + 10);
	c[0] += (ft_isdigit(s[1])) ? (s[1] - '0') : (s[1] - 'A' + 10);
	c[1] = (ft_isdigit(s[2])) ? 16 * (s[2] - '0') : 16 * (s[2] - 'A' + 10);
	c[1] += (ft_isdigit(s[3])) ? (s[3] - '0') : (s[3] - 'A' + 10);
	c[2] = (ft_isdigit(s[4])) ? 16 * (s[4] - '0') : 16 * (s[4] - 'A' + 10);
	c[2] += (ft_isdigit(s[5])) ? (s[5] - '0') : (s[5] - 'A' + 10);
	return (1);
}

static void	handle_parameter(int argc, char **argv, int color[9])
{
	int		index;
	int		top[3];
	int		mid[3];
	int		bot[3];

	index = -1;
	while (++index < 9)
		color[index] = -1;
	if (argc == 5)
	{
		if ((!ft_strtorgb(argv[2], top) || !ft_strtorgb(argv[3], mid) ||
			!ft_strtorgb(argv[4], bot)) && ft_printf("Wrong RGB value\n"))
			exit(0);
		color[0] = top[0];
		color[1] = top[1];
		color[2] = top[2];
		color[3] = mid[0];
		color[4] = mid[1];
		color[5] = mid[2];
		color[6] = bot[0];
		color[7] = bot[1];
		color[8] = bot[2];
	}
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		color[9];

	if ((argc != 2 && argc != 5))
	{
		ft_printf("Usage: ./fdf map_file [Top RGB] [Mid RGB] [Bot RGB]\n");
		exit(0);
	}
	handle_parameter(argc, argv, color);
	fdf = fdf_init(color);
	color_init(fdf);
	read_map_size(argv[1], fdf);
	read_map(argv[1], fdf);
	draw_grid(fdf);
	mlx_hook(fdf->win, 2, 0, &key_func, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
