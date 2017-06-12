/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 17:28:37 by elee              #+#    #+#             */
/*   Updated: 2016/09/27 00:07:28 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long	n[2];

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	n[0] = (*str == '-') ? -1 : 1;
	(n[1] = 0) == 0 && (*str == '+' || *str == '-') ? str++ : 0;
	while (*str >= '0' && *str <= '9')
		if ((n[1] / 922337203685477580U == 1 && (*str - '0' >= 8 ||
			n[1] % 922337203685477580U >= 1)) || n[1] / 922337203685477580U > 1)
			return ((-n[0] - 1) / 2);
		else
			n[1] = n[1] * 10 + (*str++ - '0');
	return (n[0] * n[1]);
}
