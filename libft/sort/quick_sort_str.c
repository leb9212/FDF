/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:36:27 by elee              #+#    #+#             */
/*   Updated: 2016/12/21 23:10:12 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partition(char **array, int l, int r)
{
	int		i;
	int		j;

	i = l;
	j = r + 1;
	while (1)
	{
		i++;
		while (array[i] && ft_strcmp(array[i], array[l]) <= 0 && i <= r)
			i++;
		j--;
		while (array[j] && ft_strcmp(array[j], array[l]) > 0 && j >= l)
			j--;
		if (i >= j)
			break ;
		SWAP(array[i], array[j]);
	}
	SWAP(array[l], array[j]);
	return (j);
}

void		quick_sort_str(char **array, int l, int r)
{
	int	j;

	if (l < r)
	{
		j = partition(array, l, r);
		quick_sort_str(array, l, j - 1);
		quick_sort_str(array, j + 1, r);
	}
}
