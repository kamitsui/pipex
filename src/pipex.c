/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/25 15:22:53 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_args(char **cmd_args)
{
	int		j;

	j = 0;
	while (cmd_args[j] != NULL)
	{
		free(cmd_args[j]);
		j++;
	}
	free(cmd_args);
}

static void	create_process(t_pipex *pipex)
{
	int		pipefd[2];
	int		i;
	char	**cmd_args;
	pid_t	pid;
	int		status;

	i = pipex->status != 0;
	while (i < pipex->num_cmds)
	{
		cmd_args = ft_split(pipex->cmds[i], ' ');
		if (cmd_args == NULL)
			ft_perr_exit("ft_split");
		if (pipe(pipefd) == -1)
			ft_perr_exit("pipe");
		pid = fork();
		if (pid == -1)
			ft_perr_exit("fork");
		else if (pid == 0)
			child_process(pipex, pipefd, cmd_args, i);
		else
			parent_process(pipefd, &status);
		free_args(cmd_args);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	check_argc(argc);
	initialize_pipex(argc, argv, env, &pipex);
	pipex.status = set_input(&pipex);
	set_output(&pipex);
	create_process(&pipex);
//	system("leaks pipex");
	return (0);
}

// Debug code : in else (pipexple pipe)
//#include <stdio.h>// for debug
//		printf("%s\n", pipex.in_file);
//		printf("%s\n", pipex.out_file);
//		printf("mode:%d, limiter:%s\n", pipex.mode, pipex.limiter);
//		int	k = 0;
//		while (k < pipex.num_cmds)
//		{
//			printf("%s\n", pipex.cmds[k]);
//			k++;
//		}
//		printf("%d\n", pipex.num_cmds);
//		printf("\nenv:\n");
//		int	j = 0;
//		while (pipex.env[j] != NULL)
//		{
//			printf("%s\n", pipex.env[j]);
//			j++;
//		}
