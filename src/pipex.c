/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:43:55 by kamitsui          #+#    #+#             */
/*   Updated: 2023/06/06 21:41:28 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>// for debug

int	main(int argc, char **argv, char **env)
{
	if (ft_strnequ(argv[1], "here_doc", ft_strlen(argv[1])) == true)
		printf("%s\n", argv[1]);
	else
		printf("multiple pipex\n");
	printf("\narvc:%d\n", argc);
	printf("\nenv:\n");
	int	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}
