/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:20:30 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/03 19:04:46 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	size_t			i;
	unsigned char	byte_value;
	unsigned char	*byte_ptr;

	byte_value = (unsigned char) c;
	i = 0;
	byte_ptr = (unsigned char *) ptr;
	while (i < len)
	{
		byte_ptr[i] = byte_value;
		i++;
	}
	ptr = byte_ptr;
	return (ptr);
}
