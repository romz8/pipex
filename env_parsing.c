/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:01:16 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/25 18:01:19 by rjobert          ###   ########.fr       */
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
char **search_path(char *env[])
{
    int i;
    char **path_matrix;
    char *path;
    
    path = NULL;
    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH", 4))
        i++;
    if (!ft_strncmp(env[i], "PATH", 4))
        path = env[i] + 5;
    else
        path = DEF_PATH;
    path_matrix = ft_split(path, ':');
    return(path_matrix);
}

/* noew let's look for a command line function in the path and return the path exec */
char *exec_path(char **all_path, char *cmd)
{
    char *test_path;
    char *tmp_cmd;
    
    if (!all_path)
        return (NULL);
    while(*all_path)
    {
        tmp_cmd = ft_strjoin("/", cmd);
        test_path = ft_strjoin(*all_path, tmp_cmd);
        free(tmp_cmd);
        if (access(test_path, F_OK) == 0)
            return (test_path);
        free(test_path);
        all_path++;
    }
    return (NULL); //WARNING !! was malloc don't forget to free later
}

/*we build the execve with error check along the way
 1- pass arguments are input for cmd (ex : "ls -l") + the env variables
 2- we split the the cmd argument with ft_split on space : 
 "ls -l" becomes:
    arg_cmd = ["ls", "-l", NULL]
 3 - we use search_path to look for the path inside the env[] and return a split
  matrix of all path separated by :  
 4 - we search for the correct path inside the matrix with exec_path : if access 
 function return a a path, it is where the cmmd can be found, otherwise return null
 5 - if we have a null value we can now call exit as the path won't be correct
 6 - else we execve with our path and the argument*/
void    build_exec(char *arg_user, char *env[])
{
    char **arg_cmd;
    char *cmplete_path;
    char **path;

    if (!arg_user || !env)
        return;
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

void execve_bash(char *path, char **arg_cmd, char **env)
{
    if (access(path, F_OK) == 0)
    {
        if(access(path, X_OK) != 0)
            exit_error(errno, strerror(errno));
        if (execve(path, arg_cmd, env) == -1)
            exit_error(errno, strerror(errno));
    }
    exit_error(127, "command not found");
}