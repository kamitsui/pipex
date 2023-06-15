/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:00:38 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:29 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_perr_exit(char *message)
{
	perror(message);
	exit (1);
}

int	check_mode(char **argv)
{
	if (ft_strnequ(argv[1], HERE_DOC, ft_strlen(argv[1])) == 1)
		return (BIT_HERE_DOC | BIT_APPEND);
	else
		return (BIT_NORMAL | BIT_OVER_RIDE);
}

void	check_argc(int argc)
{
	char	*err_message;

	if (argc < 5)
	{
		err_message = "Insufficient arguments!\n";
		printf("%s", err_message);
		//ft_printf("%s\n", err_message);
		exit (1);
	}
}
