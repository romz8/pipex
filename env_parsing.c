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

/* first we need to iterate over the env and isolate the PATH*/
char *search_path(char *env[])
{
    int i;
    char *path;
    
    path = NULL;
    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5))
        i++;
    if (!ft_strncmp(env[i], "PATH=", 5))
        path = env[i];
    //printf("\n env path is : %s \n", path);
    return(path);
}

/* noew let's look for a command line function in the path and return the path exec */
char *exec_path(char *path, char *cmd)
{
    char *test_path;
    char **all_path;
    char *_cmd;
    int i;
    
    if (!path || !cmd)
        return(NULL);
    all_path = ft_split(path, ':');
    if (!all_path)
        return (NULL);
    i = 0;
    _cmd = ft_strjoin("/", cmd);
    if (!_cmd)
        return (NULL);
    test_path = ft_strjoin(all_path[i],_cmd);
    while(access(test_path, F_OK) != 0 && all_path[++i])
    {
        free(test_path);
        test_path = ft_strjoin(all_path[i], _cmd);
    }
    free(_cmd);
    free_split(all_path);
    printf("\n cmdline path is : %s \n", test_path);
    return (test_path); //WARNING !! was malloc don't forget to free later
}

void    build_exec(char *path, char *arg_user, char *env[])
{
    char **arg_cmd;
    int i;
    char *cmplete_path;

    if (!path || !arg_user || !env)
        return;
    arg_cmd = ft_split(arg_user, ' ');
    cmplete_path = exec_path(path, arg_cmd[0]);
    if (execve(cmplete_path, arg_cmd, env))
    {
        free_split(arg_cmd);
        free(path);
        exit_bad("exec issue\n");
    }
    free_split(arg_cmd);
    free(path);
    return ;
}