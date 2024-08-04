/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:12:29 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 03:09:46 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	int_len(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	x;
	int		size;
	char	*dest;

	x = n;
	size = int_len(x);
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	size--;
	if (x == 0)
		dest[0] = '0';
	if (x < 0)
	{
		dest[0] = '-';
		x *= -1;
	}
	while (x > 0)
	{
		dest[size] = (x % 10) + 48;
		x = x / 10;
		size--;
	}
	return (dest);
}
