/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:06:03 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/11 13:31:07 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Locates the PATH environment variable from the environment variables list (envp).
This is used to find the directories where executable files are located.
*/
static char	*find_env_var_path_b(char **envp)
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
char	*get_path_cmd_b(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
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
static void	init_struct_paths_b(t_pipex_b *pipex, char **envp)
{
	pipex->env_var_paths = find_env_var_path_b(envp);
	pipex->env_var_paths_split = ft_split(pipex->env_var_paths, ':');
	if (!pipex->env_var_paths_split)
	{
		perror("Error:\nAllocation failed\n");
		exit(EXIT_FAILURE);
	}
}

//Initializes the pipex structure.
void	init_struct(t_pipex_b *pipex, char **envp)
{
	init_struct_paths_b(pipex, envp);
	pipex->here_doc_present = 0;
	pipex->file1_fd = 0;
	pipex->file2_fd = 0;
}
