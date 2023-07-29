/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:01:16 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/29 19:59:06 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* first we need to iterate over the env and isolate the PATH
1 - we receive end from the command line, it is array of char*
2 - ietrate over each env[x] while not null, iterate while first
    four chars are different than "PATH"
3 - when we found it, we return it minus the 5 first char (that are "PATH=")
4 - if there is no path in the env (extreme rare case but this is 42 school ... )
    we replace it by a pre-define PATH in the header*/
char	**search_path(char *env[])
{
	int		i;
	char	**path_matrix;
	char	*path;

	path = NULL;
	i = 0;
	if (!*env)
		path = DEF_PATH;
	else
	{
		while (env[i] && ft_strncmp(env[i], "PATH", 4))
			i++;
		if (!ft_strncmp(env[i], "PATH", 4))
			path = env[i] + 5;
		else
			path = DEF_PATH;
	}
	path_matrix = ft_split(path, ':');
	return (path_matrix);
}

/* noew let's look for a command line function 
 in the path and return the path exec */
char	*exec_path(char **all_path, char *cmd)
{
	char	*test_path;
	char	*tmp_cmd;

	if (!all_path)
		return (NULL);
	while (*all_path)
	{
		tmp_cmd = ft_strjoin("/", cmd);
		test_path = ft_strjoin(*all_path, tmp_cmd);
		free(tmp_cmd);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		all_path++;
	}
	return (NULL);
}

/*we build the execve with error check along the way
 1 - pass arguments are input for cmd (ex : "ls -l") 
 + the env variables
 2- we split the the cmd argument with ft_split on space : 
 "ls -l" becomes:
    arg_cmd = ["ls", "-l", NULL]
 2.b - special case for one command : awk. 
 it is entered as awk 'set of actions'
 so build a special case when the command entered is awk.
 3 - we use search_path to look for the path inside the env[] and return a 
 splitmatrix of all path separated by :  
 4 - we search for the correct path inside the matrix with exec_path : if access 
 function return a a path, it is where the cmmd can be found, 
 otherwise return null
 4.b - special case when the cmd is with absolute path 
 (instead of cat we enter /bin/cat) in that case the path is already here, 
 so if arg_user[0] = '\', path = arg_user
 5 - if we have a null value we can now call exit as the path won't be correct
 6 - else we execve with our path and the argument*/
void	build_exec(char *arg_user, char *env[])
{
	char	**arg_cmd;
	char	*cmplete_path;
	char	**path;

	if (!arg_user || !env)
		return ;
	if (!ft_strncmp(arg_user, "awk", 3))
		arg_cmd = special_split(arg_user, arg_user[4]);
	else
		arg_cmd = ft_split(arg_user, ' ');
	path = search_path(env);
	if (arg_user[0] == '/')
		cmplete_path = arg_user;
	else
		cmplete_path = exec_path(path, arg_cmd[0]);
	free_split(path);
	execve_bash(cmplete_path, arg_cmd, env);
	free(cmplete_path);
	return ;
}

void	execve_bash(char *path, char **arg_cmd, char **env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			exit_error(errno, strerror(errno), arg_cmd[0]);
		if (execve(path, arg_cmd, env) == -1)
			exit_error(errno, strerror(errno), arg_cmd[0]);
	}
	exit_error(127, "command not found", arg_cmd[0]);
}

/* the issue is that if argument is "awk '{action} pattern2 {action2}'"
therefore if we do a split on " " we have :
    arg_cmd[1] : '{action}
    arg_cmd[2] : pattern2
    arg_cmd[3] : {action2}'
but we need to rebuild it as execve needs to be
execve(/correctpath/awk, args, env) with args as :
    char *args[] = {"awk", "{count++} END {print count}", "input.tx
so what we do is that in build_execve, the cmd is awk, do :
1 - a split using special_split() on user arguments but this time on 
the type of "" or '' entered by the user (which is arg_user[4])
2 - the only issue is that in the arguments resulting from the split, the 
arguments[0] will be "awk " and we want to get rid of this space using
the strdup custom (we copy only intil space and free the initial word we
allocated memory for the original "awk " inside the split function)
    */
char	**special_split(char *arg_user, char c)
{
	char	**arguments;

	arguments = ft_split(arg_user, c);
	arguments[0] = strdup_custom(arguments[0], ' ');
	return (arguments);
}
