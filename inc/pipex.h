/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:01:52 by rhiguita          #+#    #+#             */
/*   Updated: 2025/05/14 21:24:35 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

int		exec_command(char **full_cmd, char **env);
void	ft_check_command(char *cmd, char **envp);
char	*ft_find_path(char **envp);
void	ft_free_memory(char **tab);
char	*ft_get_path(char **full_cmd, char **envp);
void	ft_error_file(int *file_pipe, char *file);
int		ft_command_error(char *cmd);
void	ft_is_empty(char *cmd);
#endif
