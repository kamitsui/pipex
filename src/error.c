/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:00:38 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 18:35:26 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int	ft_errno_set_status(char *cause)
{
	int		error_number;
	char	*error_message;

	error_number = errno;
	error_message = strerror(error_number);
	ft_fprintf(stderr, "bash: %s: %s\n", cause, error_message);
	return (error_number);
}

void	ft_errno_exit(char *cause)
{
	int		error_number;
	char	*error_message;

	error_number = errno;
	error_message = strerror(error_number);
	ft_fprintf(stderr, "bash: %s: %s\n", cause, error_message);
	exit (1);
}

void	ft_perr_exit(char *message)
{
	perror(message);
	exit (1);
}
