/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:48:18 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 17:25:00 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*search_command(char *cmd, char **value)
{
	char	*data;
	int		i;
	char	*tmp;
	char	*substring;

	tmp = *value;
	i = 0;
	(void)cmd;
	while (*tmp && *tmp != ':')
	{
		i++;
		tmp++;
	}
	if (!i)
		return (NULL);
	substring = ft_substr(*value, 0, i);
	data = ft_strjoin(substring, "/");
	free(substring);
	substring = ft_strjoin(data, cmd);
	free(data);
	*value = *value + i + 1;
	return (substring);
}

char	*_search_path(void)
{
	t_env	*env;
	t_list	*tmp;
	char	*value;

	value = NULL;
	tmp = g_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	search_path(t_parse *data, int i)
{
	char	*value;
	char	*str;
	int		x;

	x = -1;
	str = NULL;
	value = _search_path();
	while (x != 0 && value && ++i < 10)
	{
		if (str)
			free(str);
		str = search_command(data->cmd, &value);
		x = access(str, F_OK);
	}
	if (x == 0)
	{
		if (data->cmd)
			free(data->cmd);
		data->cmd = ft_strdup(str);
	}
	if (str)
		free(str);
}

void	run_execve(t_list *data1, char **env, int *fd, int fd_index)
{
	char	**str;
	t_parse	*data;

	data = data1->content;
	search_path(data, -1);
	data->pid = fork();
	str = NULL;
	if (!data->pid)
	{
		str = get_args(data, data1);
		create_dup(data1, fd, fd_index);
		if ((execve(data->cmd, str, env) == -1))
		{
			if (data->cmd && ft_strcmp(data->cmd, "<<"))
				printf("minishell: %s: command not found\n", data->cmd);
			execve_child_free(str);
			exit(127);
		}
	}
	if (fd && data->pid)
		clear_pipe(fd);
	waitpid(data->pid, &g_shell->exec_status, 0);
	g_shell->exec_status = WEXITSTATUS(g_shell->exec_status);
}

void	exec_others(t_list *data, char **env, int *fd, int fd_index)
{
	run_execve(data, env, fd, fd_index);
}
