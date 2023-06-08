/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:04:40 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/08 12:08:34 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_args
{
	char	*file1;
	char	*file2;
	char	**cmds;
	int		num_cmds;
	char	**env;
}	t_args;

int	multiple_pipes(int argc, char **argv, char **env);

#endif
