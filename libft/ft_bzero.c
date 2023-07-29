/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:38:17 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 17:30:07 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;
	unsigned char	*byte_ptr;

	i = 0;
	byte_ptr = (unsigned char *) ptr;
	while (i < n)
	{
		byte_ptr[i] = 0;
		i++;
	}
	ptr = (void *) byte_ptr;
}
