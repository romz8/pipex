/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:01:16 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/30 15:03:12 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Extract the PATH from environment variables in env[]
1 - we receive env from the command line, it is array of char*
if it is null (env empty), we return a matrix split of a default path
2 - else we itetrate over each env[x] while not null, iterate while first
    four chars are different than "PATH"
3 - when we found it, we return it minus the 5 first char (that are "PATH=")
4 - if there an is no path in the env (extremely rare but this is 42 school ... )
    we replace it by a pre-define PATH in the header*/
char	**search_path(char *env[])
{
	int		i;
	char	**path_matrix;
	char	*path;

	path = NULL;
	i = 0;
	if (!env || !*env)
	{
		path_matrix = ft_split(DEF_PATH, ':');
		return(path_matrix);
	}
	else
	{
		while (env[i] && ft_strncmp(env[i], "PATH", 4))
			i++;
		if (env[i])
			path = env[i] + 5;
		else
			path = DEF_PATH;
	}
	path_matrix = ft_split(path, ':');
	return (path_matrix);
}

/* now let's look for a command line function in the path and 
return the path exec 
 1 - we iterate over all path (if there are some) and
 use strjoin to to first go from cmd (like cat) to a
 cmd path (like /cat) and use strjoin again on a potential path
 2 - we free free the path_cmd and we now use the access function 
 to check if path/cmd  (like /bin/cat) exist with F_OK. 
 3 - if it does, we return (and free in another function) else
 we free and move to next potential from in all_path */
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

/*objective : we build the execve with error check along the way
inputs for execve are path (/bin/cat), an array of command info
 (ex : "ls -l" would yield {"ls, "-l", NULL}) and the env variables. 
 1- build command array : from cmd (argv) to arg_cmd ({cmd, arguments, NULL}): 
 we split the the cmd argument with ft_split on space "ls -l" from user input 
 in argv[] becomes:  arg_cmd = ["ls", "-l", NULL]
 1.b - special case for one command : awk and sed it is entered as 
 awk 'set of actions' so we apply special_split() focus around "" or ''
 2 - we use search_path to look for the path inside the env[] and return a
 splitmatrix of all path separated by ':' in LINUX environment
 3 - we search for the correct path inside the matrix with exec_path : if access
 function return a path, it is where the cmd can be found,
 otherwise return null. we will need to free afterward as we used malloc
 3.b - special case when the cmd is with absolute path
 (instead of cat user entered /bin/cat) in that case the path is already here,
 so if arg_user[0] = '/', path = arg_user (i.e. arg_cmd[0])
 3.c - special case if we have relative path (like ./script.sh) in that case
 the execve function needs arguments to be clean for special cases so we 
 apply the function relative_path_clean()
 4 - we can clean our path matrix, and free the cmplete_path after using
 execve_bash : an application of execve with special error handling
 */
void	build_exec(char *arg_user, char *env[])
{
	char	**arg_cmd;
	char	*cmplete_path;
	char	**path;

	if (!arg_user)
		return ;
	if (!ft_strncmp(arg_user, "awk", 3) || !ft_strncmp(arg_user, "sed", 3))
		arg_cmd = special_split(arg_user, find_sep(arg_user));
	else
		arg_cmd = special_split(arg_user, ' ');
	path = search_path(env);
	if (arg_user[0] == '/' || (arg_user[0] == '.' && arg_user[1] == '/'))
		cmplete_path = arg_cmd[0];
	else 
		cmplete_path = exec_path(path, arg_cmd[0]);
	if (arg_user[0] == '.' && arg_user[1] == '/')
		relative_path_clean(&arg_user, arg_cmd, &cmplete_path);
	free_split(path);
	execve_bash(cmplete_path, arg_cmd, env);
	free(cmplete_path);
	return ;
}

/* Objective : apply execve with many error handling
1 - first if the path is findable (the path reach a file that exist - 
we verify that (again) with access and F_OK) we then test several cases:
1.a - if the file is not exectutable ( a script.sh where -x- right are
not for user or group -> we return error 126 and exit message)
1.b - else we can apply execve and return the error message if issue
2 - if the path is not ok but arg_cmd[0] contains a "/" it is possible
that our command is a relative path with directory like subdir/scripth.sh
and in that case iterating or env wasn't a clear sucees, so we apply execve 
with arg_cmd[0] as path
3 - if nothing worked, command is clearly unknown -> exit error message  
*/
void	execve_bash(char *path, char **arg_cmd, char **env)
{
	if (access(path, F_OK) == 0)
	{	
		if (access(path, X_OK) != 0)
			exit_error(126, strerror(errno), arg_cmd[0]);
		if (execve(path, arg_cmd, env) == -1)
			exit_error(errno, strerror(errno), arg_cmd[0]);
	}
	else if (ft_strchr(arg_cmd[0], '/') && access(arg_cmd[0], F_OK) == 0)
	{
		if (execve(arg_cmd[0], arg_cmd, env) == -1)
			exit_error(errno, strerror(errno), arg_cmd[0]);
	}
	exit_error(127, "command not found", arg_cmd[0]);
}

/* the issue is that if argument is "awk '{action} pattern2 {action2}'"
or same usage for sed, ft_split will break our argv[] in too many parts.
Indeed if we do a split on " " (space) we have :
    arg_cmd[1] : '{action}
    arg_cmd[2] : pattern2
    arg_cmd[3] : {action2}'
but we need to rebuild it as execve needs to be
execve(/correctpath/awk, args, env) with args as :
    char *args[] = {"awk", "{count++} END {print count}", "input.tx
so we do :
1 - a split using special_split() on user arguments but this time on
the type of "" or '' entered by the user, so first iterate to find the
first ' or " in the command. We then split on this separator
2 - the only issue is that in the arguments resulting from the split, the
arguments[0] will be "awk " and we want to get rid of this space using
the strdup custom (we copy only intil space and free the initial word we
allocated memory for the original "awk " inside the split function)
    */
char	**special_split(char *arg_user, char c)
{
	char	**arguments;

	arguments = split_quotes(arg_user, c);
	arguments[0] = ft_strtrim(arguments[0], " ");
	return (arguments);
}
