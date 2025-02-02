/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:52:51 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/08 17:40:32 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
Prints an error message followed by an argument to the standard error output.
Constructs a formatted error message in a buffer,
combining the provided message and argument.
The buffer is then printed to stderr and the function returns an error indicator.
*/

int	print_error_with_arg(const char *message, const char *arg)
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
