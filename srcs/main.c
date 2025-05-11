/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:01:31 by rhiguita          #+#    #+#             */
/*   Updated: 2025/05/11 16:01:35 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int ac, char **av, char **envp)
{
    int file_pipe[2];
    pid_t id[2];
    int status;

    if (ac != 5)
        write((2, "format: file1 cmd1 cmd2 file2", 29), exit(1));
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

