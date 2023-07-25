/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:36:38 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/25 09:36:40 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int main(int argc, char *argv[], char *env[])
{
    int pipefd[2];
    int pid;
    char    *cmd;
    

    if (argc != 5)
        exit_bad("pipex takes 4 arguments\n");
    if (pipe(pipefd) == -1)
        exit_bad("Error creating the pipe\ns");
    char *path = search_path(env);
    pid = fork();
    if (pid == -1)
    {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        child_process(pipefd, argv, env);
    else
        parent_process(pipefd, argv, env, pid);
    close(pipefd[0]);
    close(pipefd[1]);
}

/*child process doing the read end (wc -l > output.txt)
1 - close the write end of the pipe as we don't use it (we read from the pipe pipefd[0])
2 - we clone the stdin we are streaming data from with the read-end of the pipe and we then close (pipefd[0]) to avoid to many duplicate fd refering the same open file table
3 - we open the output txt file (all possible openings and full permission) we will direct the output to, we clone STDOUT with it so that our cmdline function stdout exec will redirect to the fd (STDOUT is now the fd)
4 - we close our output file fd to avoid duplicate
5 - we can now use the exec function piping from pipfd[0] = STDIN and piping out to STDOUT = outputfile's fd
*/
void    child_process(int *pipefd, char *argv[], char *env[])  
{
    char *path;
    
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);  
    close(pipefd[0]);
        
    int fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);              
    dup2(fd_output, STDOUT_FILENO);
    close (fd_output);
        
    //execlp("grep", "grep", "Skywalker", NULL);
    path = search_path(env);
    build_exec(path, argv[3], env);
}
/*parent process doing the write end (< input.txt cat)
1 - close the read-end of the pipe as we don't use it (we write to pipefd[1])
2 - we clone the stdout as we are deviating STDOUT to stream data to the write-end of the pipe and we then close (pipefd[0]) to avoid to many duplicate fd refering the same open file table
3 - we open the input txt file (the file we stream data from - so readonly), we clone STDIN with it so that our cmdline function stdin exec will be replaced by fd (STDIN is now the fd)
4 - we close our output file fd to avoid duplicate
5 - we can now use the exec function piping from pipfd[0] = STDIN and piping out to STDOUT = outputfile's fd
6 - wait for the child to finish it's process to avoid to create a orphan after done writing
*/
void    parent_process(int *pipefd, char *argv[], char *env[], int pid)
{
    int     status;
    char    *path;

    close(pipefd[0]); 
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    int fd_input = open(argv[1], O_RDONLY, 0555);
    dup2(fd_input, STDIN_FILENO);
    close(fd_input);
        
    //execlp("cat", "cat", NULL);
    path = search_path(env);
    build_exec(path, argv[2], env);
    waitpid(pid, &status, 0);
}