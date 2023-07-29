/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:46:21 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/12 20:53:39 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i > 0 && s[i] == c && s[i - 1] != c && s[i + 1] != 0)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*word_insert(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		wc;

	wc = ft_wordcount(s, c);
	if (!s)
		return (NULL);
	matrix = malloc((wc + 1) * 8);
	if (!matrix)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			matrix[i] = word_insert(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	matrix[i] = NULL;
	return (matrix);
}
