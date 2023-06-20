/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:16:31 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/20 22:03:13 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "pipex.h"

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
		ft_perr_exit(err_message);
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
	pipex->dir = substr_env("PATH", env);
	free(pipex->dir);
}
	// debug code
//#include <unistd.h>// debug
//	printf("PATH |%s| initialize\n", pipex->dir);
//	char *token = ft_strtok(pipex->dir, ":");
//	while (token != NULL)
//	{
//		write(1, token, ft_strlen(token));
//		write(1, "\n", 1);
//		//printf("token:(%s)\n", token);// debug
//		token = ft_strtok(NULL, ":");
//	}
