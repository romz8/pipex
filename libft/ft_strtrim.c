/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:09:36 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 21:54:58 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*trimmed;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_find(s1[i], set) == 0)
		i++;
	if (i == len)
	{
		return (ft_strdup(""));
	}
	while (ft_find(s1[len - 1], set) == 0)
		len--;
	trimmed = ft_substr(s1, i, len - i);
	return (trimmed);
}
