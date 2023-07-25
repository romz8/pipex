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




#endif