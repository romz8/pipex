/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:55:43 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/01 22:18:50 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	find_sep(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != 34 && cmd[i] != 39)
		i++;
	return (cmd[i]);
}

/* 
count how many words are present, words being being separated by char when 
it is not preceded by escape cahracter (\). for instance the sentence if c = '
"Hello, what's up" -> 2 words (Hello, what, s up) but the sentence
"Hello, what\'s up" -> 1 word
*/
static int	wordcount(const char *s, char c)
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

/*
we insert words only when they terminate by the separator not preceded
by
1 - we count how many characters we have until the seprator without escape
and minus the separator (so it "what"\s up") -> 10 characters minus -1 : 9
and we malloc this size
2 - until we have the separator not preceded by escapa character, we
copy characters in new words only if it is not the sep character
*/

static char	*word_insert(const char *str, char c, int i, int j)
{
	char	*word;

	while (str[i] && !(str[i] == c && str[i - 1] != 92))
	{
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
	while (str[i] && !(str[i] == c && str[i - 1] != 92)) 
	{
		if (str[i] != 92)
		{
			word[j] = str[i];
			j++;
		}
		i++;
	}
	return (word);
}

/*
1 - count how many words with wordcount and malloc matrix
2 - while separator we traverse, then as soon as we encounter 
a character that is not a seperatorr and that is not preceded by
an escape character -> we fill the matrix with word insert
3 - then we traverse again until we find a separator (not preceded)        
*/
char	**split_quotes(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		wc;

	wc = wordcount(s, c);
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
			matrix[i] = word_insert(s, c, 0, 0);
			i++;
			while (*s && !(*s == c && *(s - 1) != 92))
				s++;
		}
	}
	matrix[i] = NULL;
	return (matrix);
}
