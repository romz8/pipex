/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:00:54 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/29 20:18:45 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(int err, char *txt, char *cmd)
{
	write(2, "pipex: ", 7);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, txt, ft_strlen(txt));
	write(2, "\n", 1);
	exit(err);
}

void	free_split(char **split_result)
{
	int	i;

	if (!*split_result)
		return ;
	i = 0;
	while (split_result[i])
	{
		free(split_result[i]);
		i++;
	}
}

int	split_len(char **split_result)
{
	int	i;

	if (!*split_result)
		return (0);
	i = 0;
	while (split_result[i])
		i++;
	return (i);
}

char	*strdup_custom(const char *s1, char c)
{
	char	*cpy;
	int		i;
	int		len;

	len = 0;
	while (s1[len] && s1[len] != c)
		len++;
	cpy = malloc(len + 1); 
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s1[i] != c)
			cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	free((void *) s1);
	return (cpy);
}
