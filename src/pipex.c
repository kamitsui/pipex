/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 19:41:36 by kamitsui         ###   ########.fr       */
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

static int	wait_process(pid_t pid, t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->num_cmds - 1)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	return (status);
}

static int	create_process(t_pipex *pipex)
{
	int		pipefd[2];
	int		i;
	char	**cmd_args;
	pid_t	pid;

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
			parent_process(pipefd);
		free_args(cmd_args);
		i++;
	}
	return (wait_process(pid, pipex));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		status;

	check_argc(argc);
	initialize_pipex(argc, argv, env, &pipex);
	pipex.status = set_input(&pipex);
	set_output(&pipex);
	status = create_process(&pipex);
	return (status);
}
//void code
//static char	*ft_split_cmd(const char *cmd, char c)
//{
//	int	i;
//	char	str[1024];
//	char	sep[2];
//	char	*token;
//
//	ft_strcpy(str, cmd);
//	sep[0] = c;
//	sep[1] = '\0';
//	i = 0;
//	while (str[i] != c && str[i] != '\0')
//		i++;
//	token = ft_strtok(&str[i], (const char *)sep);
//	while (token != NULL)
//	{
//	
//	}
//}
