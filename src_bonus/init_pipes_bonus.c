/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:40:56 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 18:11:45 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Initializes pipes for the pipex program with bonus features.
Allocates memory for storing pipe file descriptors
and creates the required number of pipes.
Each command (except the first and last) needs a pair of pipes
for input and output redirection.
In case of any failure in pipe creation or memory allocation,
it handles cleanup and error reporting.
*/
int	init_pipe_b(t_pipex_b *pipex)
{
	int	i;

	pipex->nb_pipes = (pipex->nb_cmds - 1);
	pipex->nb_pipefd = pipex->nb_pipes * 2;
	pipex->pipesfd = malloc(sizeof(int) * pipex->nb_pipefd);
	if (!pipex->pipesfd)
		return (ft_putstr_fd("Error:\nAllocation failed\n", 2), 0);
	i = 0;
	while (i < pipex->nb_pipes)
	{
		if (pipe(pipex->pipesfd + i * 2) == -1)
		{
			ft_putstr_fd("Error:\nPipe creation failed\n", 2);
			while (i > 0)
			{
				i--;
				close(pipex->pipesfd[i * 2]);
				close(pipex->pipesfd[i * 2 + 1]);
			}
			free(pipex->pipesfd);
			return (0);
		}
		i++;
	}
	return (1);
}
