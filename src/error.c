/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:00:38 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 17:51:11 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
