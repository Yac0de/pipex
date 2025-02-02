/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:54:03 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 17:38:55 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Checks file access permissions for the input
and output files specified in the arguments.
If access to a file is not available,
attempts to create the file if it's the output file.
Returns 1 if access is available or the file is successfully created,
otherwise returns 0.
*/

static int	check_file_access(const char *filename, int mode)
{
	int	fd;

	if (access(filename, mode) != 0)
	{
		if (mode == W_OK)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (print_error_with_arg("Error:\nCannot create ",
						filename), 0);
			close(fd);
		}
		else
			return (print_error_with_arg("Error:\nCannot access ", filename),
				0);
	}
	return (1);
}

/*
Validates the command-line input for the standard Pipex program.
Ensures the correct number of arguments are provided
and checks file access permissions.
Returns 1 if the input is valid and file access is successful,
otherwise returns 0.
*/

int	check_input(int argc, char **argv)
{
	if (argc != 5)
		return (ft_putstr_fd("Error\nUsage: ./pipex file1 cmd1 cmd2 file2\n",
				2), 0);
	if (!check_file_access(argv[1], R_OK) || !check_file_access(argv[4], W_OK))
		return (0);
	return (1);
}
