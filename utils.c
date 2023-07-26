/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:00:54 by rjobert           #+#    #+#             */
/*   Updated: 2023/07/26 15:01:10 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    exit_error(int err, char *txt)
{
    write(2, "pipex: ", 7);
    write(2, txt, ft_strlen(txt));
    write(2, "\n", 1);
    exit(err);
}
