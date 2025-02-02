/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:06:03 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 17:41:33 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Locates the PATH environment variable from the environment variables list (envp).
This is used to find the directories where executable files are located.
*/
static char	*find_env_var_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/*
Given a list of directory paths and a command name, 
this function searches for the executable file corresponding to the command.
It concatenates each path with the command
and checks if the file exists and is executable.
Returns the path of the command if found, or NULL if not found.
*/
char	*get_path_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/*
Initializes the paths structure within the pipex structure.
Extracts the PATH environment variable and splits it into individual paths.
Handles allocation failure by displaying an error and exiting.
*/
void	init_struct_paths(t_pipex *pipex, char **envp)
{
	pipex->env_var_paths = find_env_var_path(envp);
	pipex->env_var_paths_split = ft_split(pipex->env_var_paths, ':');
	if (!pipex->env_var_paths_split)
	{
		free_paths(pipex);
		exit(1);
	}
}
