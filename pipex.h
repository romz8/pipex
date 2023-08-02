/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:45:43 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/02 22:03:32 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "./libft/libft.h"

typedef struct s_command {
	char	*path;
	char	**args;
	int		malloc_path;
	int		fd;
}	t_cmd;

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void*src, size_t len);
size_t	ft_strlen(const char *str);
void	parent_process(int *pipefd, char *argv[], char *env[]);
void	child_process(int *pipefd, char *argv[], char *env[]);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**search_path(char *env[]);
char	*exec_path(char **path, char *cmd);
char	**ft_split(char const *s, char c);
void	free_split(char ***split_result);
int		split_len(char **split_result);
void	build_exec(char *arg_user, char *env[], int fd);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	exit_error(int err, char *txt, char *cmd, t_cmd **p_cmd);
void	execve_bash(t_cmd **p_cmd, char **env);
char	**special_split(char *arg_user, char c);
char	find_sep(char *cmd);
char	**split_quotes(char const *s, char c);
void	relative_path_clean(char **arg, t_cmd **p_cmd);
void	free_cmd(t_cmd **cmd);
char	*strdup_custom(const char *s1, char c);
void	fill_path(t_cmd **cmd_path, char *path, int x);
#endif
