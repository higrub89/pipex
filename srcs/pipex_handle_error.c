#include "pipex.h"

void ft_is_empty(char *cmd)
{
  while ((*cmd >= 9 && *cmd <= 13) || *cmd == ' ')
    cmd++;
  if (*cmd == '\0')
    (ft_command_error(cmd));
}