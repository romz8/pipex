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
    int status;
    char    *cmd;
    
    
    if (pipe(pipefd) == -1)
    {
        perror("Error creating the pipe");
        exit(EXIT_FAILURE);
    }
     
    char *input = "./input.txt";
    char *output = "./output.txt";
    
    pid = fork();
    if (pid == -1)
    {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /*child process doing the read end (wc -l > output.txt)
        1 - close the write end of the pipe as we don't use it (we read from the pipe pipefd[0])
        2 - we clone the stdin we are streaming data from with the read-end of the pipe and we then close (pipefd[0]) to avoid to many duplicate fd refering the same open file table
        3 - we open the output txt file (all possible openings and full permission) we will direct the output to, we clone STDOUT with it so that our cmdline function stdout exec will redirect to the fd (STDOUT is now the fd)
        4 - we close our output file fd to avoid duplicate
        5 - we can now use the exec function piping from pipfd[0] = STDIN and piping out to STDOUT = outputfile's fd
        */
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);  
        close(pipefd[0]);
        
        int fd_output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0777);              
        dup2(fd_output, STDOUT_FILENO);
        close (fd_output);
        
        execlp("grep", "grep", "Skywalker", NULL);
    }
    else
    {
        /*parent process doing the write end (< input.txt cat)
        1 - close the read-end of the pipe as we don't use it (we write to pipefd[1])
        2 - we clone the stdout as we are deviating STDOUT to stream data to the write-end of the pipe and we then close (pipefd[0]) to avoid to many duplicate fd refering the same open file table
        3 - we open the input txt file (the file we stream data from - so readonly), we clone STDIN with it so that our cmdline function stdin exec will be replaced by fd (STDIN is now the fd)
        4 - we close our output file fd to avoid duplicate
        5 - we can now use the exec function piping from pipfd[0] = STDIN and piping out to STDOUT = outputfile's fd
        */
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        int fd_input = open(input, O_RDONLY, 0555);
        dup2(fd_input, STDIN_FILENO);
        close(fd_input);
        
        execlp("cat", "cat", NULL);
        waitpid(pid, &status, 0);
    }
 
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concat = malloc(s1_len + s2_len + 1);
	if (!concat)
		return (NULL);
	ft_memmove(concat, s1, s1_len);
	ft_memmove(concat + s1_len, s2, s2_len);
	concat[s1_len + s2_len] = '\0';
	return (concat);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void*src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (s < d)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}