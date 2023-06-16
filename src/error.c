/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:00:38 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 16:27:16 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	ft_errno_exit(char *cause)
{
	int		error_number;
	char	*error_message;

	error_number = errno;
	error_message = strerror(error_number);
	printf("bash: %s: %s\n", cause, error_message);// Fix this !!!!!!!!!!!!!!
	exit (1);
}

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
