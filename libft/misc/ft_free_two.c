/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 16:23:16 by elee              #+#    #+#             */
/*   Updated: 2016/12/12 20:47:25 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_two(char **p)
{
	int		i;

	if (!p)
		return (0);
	i = 0;
	while (p[i])
	{
		ft_bzero(p[i], ft_strlen(p[i]));
		free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
	return (1);
}
