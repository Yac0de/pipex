/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:48:45 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/11 14:16:20 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Configures the input and output file descriptors for each child process.
For the first command, it redirects input from the input file or pipe.
For the last command, it redirects output to the output file.
For intermediate commands, it sets up pipes accordingly.
*/

static void	configure_io(t_pipex_b *pipex, int argv_index)
{
	if (argv_index == 0)
	{
		dup2(pipex->file1_fd, STDIN_FILENO);
		close(pipex->file1_fd);
	}
	else
	{
		dup2(pipex->pipesfd[2 * (argv_index - 1)], STDIN_FILENO);
		close(pipex->pipesfd[2 * (argv_index - 1)]);
	}
	if (argv_index == pipex->nb_cmds - 1)
	{
		dup2(pipex->file2_fd, STDOUT_FILENO);
		close(pipex->file2_fd);
	}
	else
	{
		dup2(pipex->pipesfd[2 * (argv_index) + 1], STDOUT_FILENO);
		close(pipex->pipesfd[2 * (argv_index) + 1]);
	}
}
/*
Executes a given command in a child process.
It splits the command into arguments, finds the executable path,
and then uses execve to run the command.
If the command is not found or cannot be executed,
it will print an error and exit the child process.
*/

static void	execute_cmd(const char *cmd, char **envp, t_pipex_b *pipex)
{
	pipex->cmd_args_split = ft_split(cmd, ' ');
	if (!pipex->cmd_args_split || !pipex->cmd_args_split[0])
	{
		ft_putstr_fd("Error:\nInvalid command arguments\n", 2);
		free_cmd_args_b(pipex->cmd_args_split, NULL);
		exit(EXIT_FAILURE);
	}
	pipex->path_cmd = get_path_cmd_b(pipex->env_var_paths_split,
			pipex->cmd_args_split[0]);
	if (!pipex->path_cmd)
	{
		ft_putstr_fd("Error:\nCommand not found ", 2);
		print_error_with_arg_b("or not authorized to be executed ", cmd);
		free_cmd_args_b(pipex->cmd_args_split, pipex->path_cmd);
		exit(EXIT_FAILURE);
	}
	execve(pipex->path_cmd, pipex->cmd_args_split, envp);
}

/*
Creates a child process for each command.
It calls `fork` and then uses other functions to set up IO redirection
and execute the command.
If the fork fails, it will print an error and exit.
*/

static void	child(const char *cmd, char **envp, t_pipex_b *pipex,
		int argv_index)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		ft_putstr_fd("Error:\nFork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pipex->pid == 0)
	{
		configure_io(pipex, argv_index);
		execute_cmd(cmd, envp, pipex);
	}
	if (argv_index != 0)
		close(pipex->pipesfd[2 * (argv_index - 1)]);
	if (argv_index != pipex->nb_cmds - 1)
		close(pipex->pipesfd[2 * argv_index + 1]);
}

/*
Iterates over all commands passed as arguments
and creates a child process for each command.
This function is the orchestrator for setting up the pipeline of commands.
*/

void	children_b(t_pipex_b *pipex, char **argv, char **envp)
{
	int		i;
	int		status;
	pid_t	pid_child;

	i = 0;
	while (i < pipex->nb_cmds)
	{
		child(argv[i + 2 + pipex->here_doc_present], envp, pipex, i);
		i++;
	}
	pid_child = wait(&status);
	while (pid_child > 0)
		pid_child = wait(&status);
}
