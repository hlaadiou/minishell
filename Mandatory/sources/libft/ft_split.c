/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:01:35 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 03:09:46 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	size_t	wc(char const *s, char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (in_set(s[i], set))
			i++;
		if (s[i])
			count++;
		while (s[i] && !in_set(s[i], set))
			i++;
	}
	return (count);
}

static	void	clean(char **d)
{
	size_t	i;

	i = 0;
	while (d[i])
		free(d[i++]);
	free(d);
}

static	char	**build(char **dest, char const *s, char *set, size_t size)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	while (i < size)
	{
		while (s[start] && in_set(s[start], set))
			start++;
		end = start;
		while (s[end] && !in_set(s[end], set))
			end++;
		dest[i] = ft_substr(s, start, (end - start));
		if (!dest[i])
		{
			clean(dest);
			return (0);
		}
		start = end;
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_split(char const *s, char *set)
{
	size_t	total;
	char	**dest;

	if (!s)
		return (0);
	total = wc(s, set);
	dest = (char **)malloc((total + 1) * sizeof(char *));
	if (!dest)
		return (0);
	return (build(dest, s, set, total));
}
