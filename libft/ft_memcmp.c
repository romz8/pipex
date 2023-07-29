/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:06:34 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/04 17:54:59 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*byte_s1;
	unsigned char	*byte_s2;

	i = 0;
	byte_s1 = (unsigned char *) s1;
	byte_s2 = (unsigned char *) s2;
	while (i < n)
	{
		if (*(byte_s1 + i) != *(byte_s2 + i))
			return (*(byte_s1 + i) - *(byte_s2 + i));
		i++;
	}
	return (0);
}
