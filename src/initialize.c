/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:16:31 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/16 17:24:24 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>// delete this !!!!!!

static int	check_mode(char **argv)
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
		printf("%s", err_message);// Fix this !!!!!!!!!!!!!!!!
		exit (1);
	}
}

void	initialize_pipex(int argc, char **argv, char **env, t_pipex *pipex)
{
	int	offset;

	pipex->in_file = argv[1];
	pipex->out_file = argv[argc - 1];
	pipex->mode = check_mode(argv);
	offset = (pipex->mode & BIT_HERE_DOC) > 0;
	pipex->limiter = argv[2];
	pipex->cmds = &argv[2 + offset];
	pipex->num_cmds = argc - 3 - offset;
	pipex->env = env;
}
