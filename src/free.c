/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:02:03 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 17:42:32 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Frees memory allocated for command arguments and the executable path.
Iterates through each argument in the command arguments array and frees them,
and then frees the array itself and the path of the executable.
*/

void	free_cmd_args(char **cmd_args_split, char *path_cmd)
{
	int	i;

	i = 0;
	while (cmd_args_split[i])
	{
		free(cmd_args_split[i]);
		i++;
	}
	free(cmd_args_split);
	free(path_cmd);
}
/*
Frees the memory allocated for the PATH environment variable split into paths.
Closes file descriptors for the input and output files.
Iterates through the split PATH environment variable, freeing each path,
and then frees the array holding these paths.
*/

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->file1_fd);
	close(pipex->file2_fd);
	while (pipex->env_var_paths_split[i])
	{
		free(pipex->env_var_paths_split[i]);
		i++;
	}
	free(pipex->env_var_paths_split);
}
