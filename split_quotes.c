/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:55:43 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/30 15:55:49 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordcount(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i > 0 && s[i] == c && s[i - 1] != 92 && s[i + 1] != 0)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*word_insert(const char *str, char c)
{
	int		i;
    int     j;
	char	*word;

	i = 0;
    j = 0;
	while (str[i])   //we count how many words minus the / appearing
    {
		if (str[i] == c && str[i - 1] != 92)
            break;
        if (str[i] == 92)
            j++;
        i++;
    }
	word = malloc(i - j + 1);
	if (!word)
		return (NULL);
    word[i] = '\0';
	i = 0;
    j = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != 92)
            break;
        if (str[i] != 92 )
        {
            word[j] = str[i];
            j++;
        }
		i++;

	}
	return (word);
}

char	**split_quotes(char const *s, char c)
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
		if (*s && *s != c && *(s - 1) != 92)
		{
			matrix[i] = word_insert(s, c);
			i++;
			while (*s)
            {
                if(*s == c && *(s - 1) != 92)
                    break ;
                s++;
            }
		}
	}
	matrix[i] = NULL;
	return (matrix);
}

