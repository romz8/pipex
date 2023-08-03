/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:07:16 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/02 22:09:45 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*display error message as shell would for a cmd 1 | cmd2 error 
if the struct path_cmd is provided, we clear all inside */
void	exit_error(int err, char *txt, char *cmd, t_cmd **p_cmd)
{
	write(2, "pipex: ", 7);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, txt, ft_strlen(txt));
	write(2, "\n", 1);
	if (p_cmd)
		free_cmd(p_cmd);
	exit(err);
}

/*to clear matrices of strings used for path search*/
void	free_split(char ***split_result)
{
	int	i;

	if (!*split_result || !split_result)
		return ;
	i = 0;
	while ((*split_result)[i])
	{
		free((*split_result)[i]);
		i++;
	}
	free(*split_result);
	*split_result = NULL;
}

/*
clear all what's inside the process due to error
1 - close the fd
2 - if path was malloc, free
3 - clear all arguments (malloc string) from split matrix 
4 - clear the matrix itslef and set to null
*/
void	free_cmd(t_cmd **cmd)
{
	int	i;

	if (!*cmd)
		return ;
	close((*cmd)->fd);
	if ((*cmd)->malloc_path == 1)
	{
		free((*cmd)->path);
		(*cmd)->path = NULL;
	}
	i = 0; 
	while ((*cmd)->args[i])
	{
		free((*cmd)->args[i]);
		i++;
	}
	free((*cmd)->args);
	(*cmd)-> args = NULL;
	free(*cmd);
	*cmd = NULL;
}
