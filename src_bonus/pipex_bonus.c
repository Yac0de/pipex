/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:02:35 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/11 14:12:54 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Main function for Pipex program with bonus features. 
It initializes the pipex structure,
checks the input arguments, and sets up file descriptors.
Handles the 'here_doc' feature if present, otherwise opens the input file.
Opens the output file and calculates the number of commands.
Initializes pipes, executes the commands with children processes,
and waits for their completion.
If 'here_doc' is used, it cleans up the temporary file.
Frees allocated paths before exiting.
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_b	pipex;

	init_struct(&pipex, envp);
	if (!check_input_b(argc, argv, &pipex))
		return (free_paths_b(&pipex), 1);
	if (pipex.here_doc_present)
		here_doc_b(argv[2], &pipex);
	else
		pipex.file1_fd = open(argv[1], O_RDONLY);
	if (pipex.file1_fd == -1)
		return (print_error_with_arg_b("Error:\nCannot open ", argv[1]), 1);
	pipex.file2_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (pipex.file2_fd == -1)
		return (print_error_with_arg_b("Error:\nCannot open ", argv[argc - 1]),
			1);
	pipex.nb_cmds = argc - 3 - pipex.here_doc_present;
	if (!init_pipe_b(&pipex))
		return (1);
	children_b(&pipex, argv, envp);
	waitpid(-1, NULL, 0);
	if (pipex.here_doc_present)
		unlink(".tmp_file_here_doc.txt");
	free(pipex.pipesfd);
	free_paths_b(&pipex);
	return (0);
}
