/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:21:44 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/09 23:31:27 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_bsize(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*malloc_dynam(long nb, int size, int neg)
{
	char	*nbr;

	if (nb != 0)
		nbr = malloc(size + 1);
	else
		return (ft_strdup("0"));
	if (!nbr)
		return (NULL);
	nbr[size] = '\0';
	while (--size)
	{
		nbr[size] = nb % 10 + '0';
		nb /= 10;
	}
	if (neg == 1)
		nbr[0] = '-';
	else
		nbr[0] = nb % 10 + '0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	long	nb;
	int		neg;
	int		size;

	nb = n;
	neg = 0;
	if (n < 0)
	{
		size = number_bsize(n) + 1;
		neg = 1;
		nb *= -1;
	}
	else
		size = number_bsize(n);
	nbr = malloc_dynam(nb, size, neg);
	return (nbr);
}
