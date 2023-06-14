/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/14 20:50:23 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
//#include <stdbool.h>
#include <stdio.h>// for debug
#include <unistd.h>// for debug

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
//	pipex->end_status = 0;
}
//	printf("offset:%d\n", offset);
//	printf("argv[2 + offset]:%s\n", argv[2 + offset]);
//	printf("num_cmds:%d\n", pipex->num_cmds);

void	free_args(char **cmd_args)
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

void	create_process(t_pipex *pipex, int pipefd[2])
{
	pid_t	pid;
	int		i;
	char	**cmd_args;

	i = 0;
	while (i < pipex->num_cmds)
	{
		cmd_args = ft_split(pipex->cmds[i], ' ');
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
			child_process(pipex, pipefd, cmd_args, i);
		free_args(cmd_args);
		i++;
	}
}
//	printf("num_cmds: %d\n", pipex->num_cmds);
//		printf("pid:%d\n", pid);// child pid

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		pipefd[2];
	int		i;
	int		status;

	check_argc(argc);
	initialize_pipex(argc, argv, env, &pipex);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	create_process(&pipex, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	i = 0;
	while (i < pipex.num_cmds)
	{
		wait(&status);
		i++;
	}
//	return (pipex.end_status);
	return (0);
}
// Debug code : in else (pipexple pipe)
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
