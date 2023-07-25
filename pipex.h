/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:45:43 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/25 09:45:47 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void*src, size_t len);
size_t	ft_strlen(const char *str);
void    parent_process(int *pipefd, char *argv[], char *env[], int pid);
void    child_process(int *pipefd, char *argv[], char *env[]);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *search_path(char *env[]);
char *exec_path(char *path, char *cmd);
char	**ft_split(char const *s, char c);
void free_split(char **split_result);
int split_len(char **split_result);
void    build_exec(char *path, char *arg_user, char *env[]);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void  exit_bad(char *message);

#endif