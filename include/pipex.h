/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:04:40 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/14 20:43:26 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END	0
# define WRITE_END	1
# define HERE_DOC	"here_doc"

# define BIT_NORMAL		0x00
# define BIT_HERE_DOC	0x01
# define BIT_OVER_RIDE	0x02

typedef struct s_pipex
{
	char	*in_file;
	char	*out_file;
	char	**cmds;
	int		num_cmds;
	char	**env;
	int		n_status;
	int		mode;
	char	*limiter;
}	t_pipex;

//int		pipexple_pipex(int argc, char **argv, char **env);
void	set_input(t_pipex *pipex, int pipfd[2], int i);
void	set_output(t_pipex *pipex, int pipfd[2], int i);
int	check_mode(char **argv);
void	check_argc(int argc);
void	ft_perr_exit(char *message);
void	child_process(t_pipex *pipex, int pipefd[2], char *arguments[], int i);

#endif
