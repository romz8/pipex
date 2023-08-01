/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:00:54 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/01 20:08:33 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*display error message as shell would for a cmd 1 | cmd2 error */
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

/*to clear matrices of strings used for path search*/
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

/*to copy a string but without its end space*/
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

/* for the special case of a relative path ./subfoler/path
there can be weird test like :
 ./script\"quote.sh that is correct in shell but execve can not
 accept the escape character (\) in path nor command so we
 need to clean both and end-up with ./script"quote.sh 
 (which woulld be wrong for cdl but correct for execve)
 */
void	relative_path_clean(char **arg, char **cmd, char **cmplete_path)
{
	int	i;

	if (!*arg || !*cmd || !*cmplete_path)
		return ;
	if (ft_strchr(*arg, 32))
		exit_error(127, "No such file or directory", cmd[0]);
	i = 0;
	while (cmd[i])
	{
		if (ft_strnstr(cmd[i], "\"", ft_strlen(cmd[i])))
		{
			ft_strtrim(cmd[i], "\\");
		}
		if (ft_strnstr(cmd[i], "\'", ft_strlen(cmd[i])))
		{
			ft_strtrim(cmd[i], "\\");
		}
		i++;
	}
	if (ft_strnstr(*cmplete_path, "\"", ft_strlen(*cmplete_path)))
		*cmplete_path = cmd[0];
	if (ft_strnstr(*cmplete_path, "\'", ft_strlen(*cmplete_path)))
		*cmplete_path = cmd[0];
}
