/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:52:51 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 16:10:00 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Prints an error message concatenated with an argument string
to the standard error output.
Formats the final message into a buffer
before sending it to stderr.
The function is used to provide detailed error messages
throughout the program.
*/
int	print_error_with_arg_b(const char *message, const char *arg)
{
	char	buffer[1024];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (message[i])
		buffer[j++] = message[i++];
	i = 0;
	while (arg && arg[i])
		buffer[j++] = arg[i++];
	buffer[j++] = '\n';
	buffer[j] = '\0';
	return (ft_putstr_fd(buffer, 2), 2);
}
