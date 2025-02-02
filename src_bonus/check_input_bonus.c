/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:54:03 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/11 14:06:17 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Validates the input arguments for the Pipex program with bonus features.
Checks if the correct number of arguments is provided.
If 'here_doc' is present,
it checks for the right number of arguments for this mode.
Verifies access permissions for the input and output files.
If necessary, creates the output file with the appropriate permissions.
*/
static int	check_file_access(const char *filename, int mode)
{
	int	fd;

	if (access(filename, mode) != 0)
	{
		if (mode == W_OK)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (print_error_with_arg_b("Error:\nCannot create ",
						filename), 0);
			close(fd);
		}
		else
			return (print_error_with_arg_b("Error:\nCannot access "
					, filename), 0);
	}
	return (1);
}

/*
Main input checking function for the Pipex program with bonus features.
Verifies the number of arguments and identifies if 'here_doc' is specified.
Calls check_file_access to verify access permissions
for the input and output files.
*/

int	check_input_b(int argc, char **argv, t_pipex_b *pipex)
{
	if (argc < 2)
		return (ft_putstr_fd("Error\nNumber of invalid arguments\n",
				2), 0);
	else if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->here_doc_present = 1;
		if (argc < 6)
			return (ft_putstr_fd("Error\nNumber of invalid arguments\n",
					2), 0);
	}
	else if (argc < 5)
		return (ft_putstr_fd("Error\nNumber of invalid arguments\n",
				2), 0);
	if (pipex->here_doc_present)
	{
		if (!check_file_access(argv[argc - 1], W_OK))
			return (0);
	}
	else if (!check_file_access(argv[1], R_OK)
		|| !check_file_access(argv[argc - 1], W_OK))
		return (0);
	return (1);
}
