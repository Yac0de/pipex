/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:48:45 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/10 22:49:34 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Executes the first command in the Pipex program.
Redirects the standard input from the input file
and the standard output to the write end of the pipe.
Splits the first command into arguments and attempts to execute it.
In case the command is not found or fails to execute,
it frees resources and exits with an error.
*/
void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.file1_fd, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	pipex.cmd1_args_split = ft_split(argv[2], ' ');
	pipex.path_cmd1 = get_path_cmd(pipex.env_var_paths_split,
			pipex.cmd1_args_split[0]);
	if (!pipex.path_cmd1)
	{
		free_cmd_args(pipex.cmd1_args_split, pipex.path_cmd1);
		ft_putstr_fd("Error:\nCommand not found", 2);
		print_error_with_arg(" or not authorized to be executed ", argv[2]);
		free_paths(&pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex.path_cmd1, pipex.cmd1_args_split, envp);
}

/*
Executes the second command in the Pipex program.
Redirects the standard input from the read end of the pipe
and the standard output to the output file.
Splits the second command into arguments and attempts to execute it.
In case the command is not found or fails to execute,
it frees resources and exits with an error.
*/
void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[1]);
	dup2(pipex.file2_fd, STDOUT_FILENO);
	pipex.cmd2_args_split = ft_split(argv[3], ' ');
	pipex.path_cmd2 = get_path_cmd(pipex.env_var_paths_split,
			pipex.cmd2_args_split[0]);
	if (!pipex.path_cmd2)
	{
		free_cmd_args(pipex.cmd2_args_split, pipex.path_cmd2);
		ft_putstr_fd("Error:\nCommand not found", 2);
		print_error_with_arg(" or not authorized to be executed ", argv[3]);
		free_paths(&pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex.path_cmd2, pipex.cmd2_args_split, envp);
}
