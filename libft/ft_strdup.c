/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:09:45 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 17:21:13 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s1);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	cpy = ft_memcpy((void *) cpy, (const void *) s1, len + 1);
	return (cpy);
}
