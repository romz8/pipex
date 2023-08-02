/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:00:54 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/02 22:11:56 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*to measure depth of those matrices*/
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

/* for the special case of a relative path ./subfoler/path
there can be weird test like :
 ./script\"quote.sh that is correct in shell but execve can not
 accept the escape character (\) in path nor command so we
 need to clean both and end-up with ./script"quote.sh 
 (which woulld be wrong for cdl but correct for execve)
 */
void	relative_path_clean(char **arg, t_cmd **p_cmd)
{
	int	i;

	if (!*arg || !*p_cmd)
		return ;
	if (ft_strchr(*arg, 32))
		exit_error(127, "No such file or directory", (*p_cmd)->args[0], p_cmd);
	i = 0;
	while ((*p_cmd)->args[i])
	{
		if (ft_strnstr((*p_cmd)->args[i], "\"", ft_strlen((*p_cmd)->args[i])))
		{
			ft_strtrim((*p_cmd)->args[i], "\\");
		}
		if (ft_strnstr((*p_cmd)->args[i], "\'", ft_strlen((*p_cmd)->args[i])))
		{
			ft_strtrim((*p_cmd)->args[i], "\\");
		}
		i++;
	}
	if (ft_strnstr((*p_cmd)->path, "\"", ft_strlen((*p_cmd)->path)))
		(*p_cmd)->path = (*p_cmd)->args[0];
	if (ft_strnstr((*p_cmd)->path, "\'", ft_strlen((*p_cmd)->path)))
		(*p_cmd)->path = (*p_cmd)->args[0];
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

void	fill_path(t_cmd **cmd_path, char *path, int x)
{
	if (!*cmd_path)
		return ;
	(*cmd_path)->path = path;
	(*cmd_path)->malloc_path = x;
	return ;
}
