/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:36:38 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/29 20:10:03 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int	pipefd[2];
	int	pid;

	if (argc != 5)
		exit_error(EXIT_FAILURE, "please enter 4 arguments", NULL);
	if (pipe(pipefd) == -1)
		exit_error(errno, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
		exit_error(errno, strerror(errno), NULL);
	if (pid == 0)
		child_process(pipefd, argv, env);
	else
		parent_process(pipefd, argv, env, pid);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

/*parent process doing from read-end to output.txt)
1 - close the write end of the pipe as we don't use it 
(we read from the pipe pipefd[0])
2 - we clone the stdin we are streaming data from with the read-end of the pipe 
and we then close (pipefd[0]) to avoid to many duplicate fd refering the same 
open file table
3 - we open the output txt file (all possible openings and full permission)
we will direct the output to, we clone STDOUT with it so that our cmdline 
function stdout exec will redirect to the fd (STDOUT is now the fd)
4 - we close our output file fd to avoid duplicate
5 - we can now use the exec function piping from pipfd[0] = STDIN and 
piping out to STDOUT = outputfile's fd
*/
void	parent_process(int *pipefd, char *argv[], char *env[], int pid)
{
	int	status;
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		exit_error(errno, strerror(errno), argv[4]);
	waitpid(pid, &status, WNOHANG); 
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	build_exec(argv[3], env);
}

/*child process doing from inutfile to the write-end 
1 - close the read-end of the pipe as we don't use it 
(we write to pipefd[1])
2 - we clone the stdout as we are deviating STDOUT to stream data to 
the write-end  of the pipe and we then close (pipefd[0]) to avoid to many 
duplicate fd refering the same open file table
3 - we open the input txt file (the file we stream data from - so readonly), 
we clone STDIN with it so that our cmdline function stdin exec will be replaced 
by fd (STDIN is now the fd)
4 - we close our output file fd to avoid duplicate
5 - we can now use the exec function piping from pipfd[0] = STDIN and piping out 
to STDOUT = outputfile's fd
6 - wait for the child to finish it's process to avoid to create a 
orphan after done writing 
*/
void	child_process(int *pipefd, char *argv[], char *env[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0666);
	if (fd == -1)
		exit_error(errno, strerror(errno), argv[1]);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	build_exec(argv[2], env);
	exit(EXIT_SUCCESS);
}
