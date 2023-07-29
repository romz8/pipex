/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:19:00 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/29 19:47:56 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			j;
	char			*sub;

	if (!s)
		return (NULL);
	if ((size_t) start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	i = 0;
	j = start;
	while (j < ft_strlen(s) && i < len)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = '\0';
	return (sub);
}
