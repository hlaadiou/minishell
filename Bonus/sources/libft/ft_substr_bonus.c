/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:29:52 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*sub;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	l = ft_strlen(s);
	if (len <= l)
		sub = (char *)malloc((len + 1) * sizeof(char));
	else
		sub = (char *)malloc((l - start + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[start] && start < l && s[start + j] && j < len)
		sub[i++] = s[start + j++];
	sub[i] = '\0';
	return (sub);
}
