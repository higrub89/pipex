/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_handle_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:05:09 by rhiguita          #+#    #+#             */
/*   Updated: 2025/05/15 18:05:12 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_is_empty(char *cmd)
{
	while ((*cmd >= 9 && *cmd <= 13) || *cmd == ' ')
		cmd++;
	if (*cmd == '\0')
		(ft_command_error(cmd));
}
