#include "pipex.h"

void ft_error_file(int *file_pipe, char *file)
{
  close(file_pipe[0]);
  close(file_pipe[1]);
  perror(file);
}

char *ft_find_path(char **envp)
{
  char *value_path;

  while(*envp != NULL)
  {
    value_path = *envp++;
    if (ft_strncmp(value_path, "PATH=", 5) == 0)
    {
      value_path = value_path + 5;
      return (value_path);
    }
  }
  return (NULL);
}

void ft_free_memory(char **tab)
{
  size_t i;

  i = 0;
  while (tab[i])
  {
    free(tab[i]);
    i++;
  }
  free(tab);
}

char *ft_get_path(char **full_cmd, char **envp)
{
  char *cmd;
  char *path;
  char **path_split;
  int i;
  char *new;

  i = 0;
  path = ft_find_path(envp);
  if (path == NULL)
  {
    new = ft_strdup(full_cmd[0]);
    (ft_command_error(new));
  }
  cmd = ft_strjoin("/", full_cmd[0]);
  path_split = ft_split(path, ':');
  while (path_split[i] != NULL)
  {
    path = ft_strjoin(path_split[i], cmd);
    if (access(path, F_OK | X_OK) == 0)
      return (free(cmd), ft_free_memory(path_split), path);
    free(path);
    i++;
  }
  (free(cmd), ft_free_memory(path_split));
  return (NULL);
}

void ft_check_command(char *cmd, char **envp)
{
  char **s_cmd;
  char *path;

  ft_is_empty(cmd);
  s_cmd = ft_split(cmd, ' ');
  if (access(s_cmd[0], F_OK | X_OK) == 0 && s_cmd[0][0] == '/')
  {
    if (execve(s_cmd[0], s_cmd, envp) == -1)
      (ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
  }
  if (access(s_cmd[0], F_OK | X_OK) == 0 && ft_strnstr(s_cmd[0], "./", 2))
  {
    if (execve(s_cmd[0], s_cmd, envp) == -1)
      (ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
  }
  else if (access(s_cmd[0], F_OK | X_OK) != 0 &&
  ft_strchr(s_cmd[0], '/'))
    (ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
  else
  {
    path = ft_get_path(s_cmd, envp);
    if (path == NULL || execve(path, s_cmd, envp) == -1)
      (ft_command_error(s_cmd[0]), ft_free_memory(s_cmd));
    ft_free_memory(s_cmd);
    free(path);
  }
}