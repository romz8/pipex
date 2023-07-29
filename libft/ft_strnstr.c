/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:40:31 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 19:31:06 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *target, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_target;

	i = 0;
	len_target = ft_strlen(target);
	if (!len_target || str == target)
		return ((char *) str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == target[j] && i + j < len)
			j++;
		if (target[j] == '\0')
			return ((char *) &str[i]);
		i++;
	}
	return (NULL);
}
