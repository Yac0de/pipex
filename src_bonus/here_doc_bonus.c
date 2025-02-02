/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:46:06 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/11 14:04:25 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// Writes a specified number of characters and add a newline
// from a string to a file descriptor
static void	ft_putnendl_fd(char *s, int fd, int n)
{
	if (!s || n < 0)
		return ;
	while (*s && n--)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

/*
Creates a temporary file for 'here_doc' functionality. 
If needed, create the file, open it and handles errors
if the file cannot be opened.
*/
int	create_here_doc_file(void)
{
	int	fd;

	fd = open(".tmp_file_here_doc.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error:\nCannot open tmp_file_here_doc\n", 2);
		exit(1);
	}
	return (fd);
}

/*
// Handles the 'here_doc' input from the standard input
until the limiter is reached.
Writes each line of input to the temporary file, excluding the limiter.
*/
void	write_to_here_doc(int fd, char *limiter)
{
	char	*line;
	char	*limiter_with_newline;

	limiter_with_newline = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			exit(1);
		if (ft_strcmp(line, limiter_with_newline) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			ft_putnendl_fd(line, fd, ft_strlen(line) - 1);
			free(line);
		}
	}
	free(limiter_with_newline);
}

/*
Main function to handle the 'here_doc' feature.
Creates a temporary file, writes user input to it based on the limiter,
and then sets up the file descriptor
to be used as standard input for the first command.
*/
void	here_doc_b(char *limiter, t_pipex_b *pipex)
{
	int	fd_here_doc;

	fd_here_doc = create_here_doc_file();
	write_to_here_doc(fd_here_doc, limiter);
	close(fd_here_doc);
	pipex->file1_fd = open(".tmp_file_here_doc.txt", O_RDONLY);
	if (pipex->file1_fd == -1)
	{
		ft_putstr_fd("Error:\nCannot open .tmp_file_here_doc.txt", 2);
		exit(1);
	}
}
