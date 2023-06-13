/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:10:31 by mmisskin          #+#    #+#             */
/*   Updated: 2023/06/13 21:13:41 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check(size_t res, size_t old)
{
	if ((res / 10) == old)
		return (1);
	return (0);
}

static	size_t	fill(const char *str, int sign)
{
	size_t	res;
	size_t	o_res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		o_res = res;
		res *= 10;
		if (!check(res, o_res) && sign == -1)
			return (0);
		else if (!check(res, o_res))
			return (-1);
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}

size_t	ft_atoi(const char *str)
{
	int					index;
	int					sign;

	index = 0;
	sign = 1;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	return (fill(&str[index], sign));
}
