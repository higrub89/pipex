/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:01:31 by rhiguita          #+#    #+#             */
/*   Updated: 2025/05/15 13:15:46 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_command_error(char *cmd)
{
	printf("%s\ncomando", cmd);
	cmd = ft_strjoin(cmd, "\n");
	write(2, "command not fount: ", 20);
	write(2, cmd, ft_strlen(cmd));
	free(cmd);
	exit(127);
}

static pid_t	process_one(char **av, char **envp, int *file_pipe)
{
	int		fd;
	pid_t	id;

	id = fork();
	if (id == -1)
		(perror("Error:"), exit(1));
	if (id == 0)
	{
		fd = open(av[1], O_RDONLY, 0664);
		if (fd < 0)
			(ft_error_file(file_pipe, av[1]), exit(1));
		dup2(fd, 0);
		dup2(file_pipe[1], 1);
		close(file_pipe[0]);
		close(file_pipe[1]);
		close(fd);
		ft_check_command(av[2], envp);
	}
	return (id);
}

static pid_t	process_two(char **av, char **envp, int *file_pipe, int ac)
{
	int		fd;
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		fd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd < 0)
			(ft_error_file(file_pipe, av[ac - 1]), exit(1));
		dup2(file_pipe[0], 0);
		dup2(fd, 1);
		close(file_pipe[1]);
		close(file_pipe[0]);
		close(fd);
		ft_check_command(av[ac - 2], envp);
	}
	return (id);
}

int	main(int ac, char **av, char **envp)
{
	int		file_pipe[2];
	pid_t	id[2];
	int		status;

	if (ac != 5)
		(write(2, "format: file1 cmd1 cmd2 file2", 29), exit(1));
	if (pipe(file_pipe) == -1)
		(perror("Error:"), exit(1));
	id[0] = process_one(av, envp, file_pipe);
	id[1] = process_two(av, envp, file_pipe, ac);
	close(file_pipe[0]);
	close(file_pipe[1]);
	waitpid(id[0], &status, 0);
	waitpid(id[1], &status, 0);
	exit(WEXITSTATUS(status));
	return (0);
}
