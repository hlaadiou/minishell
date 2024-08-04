/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:29:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	x;
	char	*trim;

	if (!s1 || !set)
		return (0);
	if (!*s1)
		return (ft_strdup(""));
	i = 0;
	x = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	while (ft_strrchr(set, s1[j]) && j > 0)
		j--;
	if (i > j)
		return (ft_strdup(""));
	trim = (char *)malloc(((j - i) + 2) * sizeof(char));
	if (!trim)
		return (0);
	while (i <= j)
		trim[x++] = s1[i++];
	trim[x] = 0;
	return (trim);
}
