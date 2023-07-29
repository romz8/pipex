/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:02:24 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 20:30:38 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat = malloc(s1_len + s2_len + 1);
	if (!concat)
		return (NULL);
	ft_memmove(concat, s1, s1_len);
	ft_memmove(concat + s1_len, s2, s2_len);
	concat[s1_len + s2_len] = '\0';
	return (concat);
}
