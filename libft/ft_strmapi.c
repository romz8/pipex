/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:44:53 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/10 18:52:28 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*modif;

	len = ft_strlen(s);
	modif = ft_strdup(s);
	if (!modif)
		return (NULL);
	if (!s || !f)
		return (modif);
	i = 0;
	while (modif[i])
	{
		modif[i] = (*f)(i, modif[i]);
		i++;
	}
	return (modif);
}
