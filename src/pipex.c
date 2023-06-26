/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:59:34 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/26 21:14:34 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"// debug
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

static int	create_process(t_pipex *pipex)
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
//		if (ft_strchr(cmd_args[0], '/') != NULL && access(cmd_args[0], F_OK | X_OK) != 0)
//		{
//			ft_fprintf(STDERR_FILENO, "bash: %s: command not found\n", pipex->cmds[i]);// ??/exit 127 not do
//			status = 127;
//		}
//		else
//		{
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
	pid_t	terminal_pid;
	while (i > 0)
	{
		i--;
		terminal_pid = waitpid(pid - i, &status, 0);
	}
	if (terminal_pid == -1)
		ft_errno_exit("waitpid");
	int		exit_status = 0;
	if (WIFEXITED(status))
	{
// Child process exited normally
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status)) {
// Child process terminated by a signal
		int signal_number = WTERMSIG(status);
		return (signal_number);
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	check_argc(argc);
	initialize_pipex(argc, argv, env, &pipex);
	pipex.status = set_input(&pipex);
	set_output(&pipex);
	return (create_process(&pipex));
//	system("leaks pipex");
}
