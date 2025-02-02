/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:04:17 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/10 11:27:23 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		file1_fd;
	int		file2_fd;
	char	*env_var_paths;
	char	**env_var_paths_split;
	char	**cmd1_args_split;
	char	**cmd2_args_split;
	char	*path_cmd1;
	char	*path_cmd2;
}			t_pipex;

void		init_struct_paths(t_pipex *pipex, char **envp);
int			check_input(int argc, char **argv);
int			print_error_with_arg(const char *message, const char *arg);
char		*get_path_cmd(char **paths, char *cmd);
void		first_child(t_pipex pipex, char *argv[], char *envp[]);
void		second_child(t_pipex pipex, char *argv[], char *envp[]);
void		free_cmd_args(char **cmd_args_split, char *path_cmd);
void		free_paths(t_pipex *pipex);

// BONUS
typedef struct s_pipex_b
{
	pid_t	pid;
	int		*pipesfd;
	int		file1_fd;
	int		file2_fd;
	char	*env_var_paths;
	char	**env_var_paths_split;
	char	**cmd_args_split;
	char	*path_cmd;
	int		here_doc_present;
	int		nb_cmds;
	int		nb_pipes;
	int		nb_pipefd;
}			t_pipex_b;

void		init_struct(t_pipex_b *pipex, char **envp);
int			check_input_b(int argc, char **argv, t_pipex_b *pipex);
int			print_error_with_arg_b(const char *message, const char *arg);
void		here_doc_b(char *limiter, t_pipex_b *pipex);
char		*get_path_cmd_b(char **paths, char *cmd);
int			init_pipe_b(t_pipex_b *pipex);
void		children_b(t_pipex_b *pipex, char **argv, char **envp);
void		free_cmd_args_b(char **cmd_args_split, char *path_cmd);
void		free_paths_b(t_pipex_b *pipex);

#endif