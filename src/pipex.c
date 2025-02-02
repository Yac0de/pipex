/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:02:35 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 17:02:23 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// Closes the two file descriptors in a pipe to prevent resource leaks.
static void	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

/*
Main function for Pipex program.
Validates input arguments and opens the input and output files.
Initializes the paths structure, creates a pipe, and forks two child processes.
Each child process executes one of the commands,
with appropriate input and output redirection.
Waits for child processes to complete and then frees allocated resources.
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (!check_input(argc, argv))
		return (1);
	pipex.file1_fd = open(argv[1], O_RDONLY);
	if (pipex.file1_fd == -1)
		return (print_error_with_arg("Error:\nCannot open ", argv[1]), 1);
	pipex.file2_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.file2_fd == -1)
		return (close(pipex.file1_fd),
			print_error_with_arg("Error:\nCannot open ", argv[4]), 1);
	init_struct_paths(&pipex, envp);
	if (pipe(pipex.pipefd) == -1)
		return (ft_putstr_fd("Error:\nPipe creation failed\n", 2), 1);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(pipex.pipefd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_paths(&pipex);
	return (0);
}
