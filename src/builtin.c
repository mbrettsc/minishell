/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:18 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 20:46:43 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_command(t_list *tmp, int *fd, int fd_index)
{
	t_parse	*data;

	data = tmp->content;
	if (fd)
		create_dup(tmp, fd, fd_index);
	if ((ft_strcmp(data->cmd, "echo") == 0)
		|| (ft_strcmp(data->cmd, "ECHO") == 0))
		exec_echo(data);
	if (ft_strcmp(data->cmd, "cd") == 0)
		exec_cd(data);
	if ((ft_strcmp(data->cmd, "pwd") == 0) 
		|| (ft_strcmp(data->cmd, "PWD") == 0))
		exec_pwd(data);
	if (ft_strcmp(data->cmd, "export") == 0)
		exec_export(data);
	if (ft_strcmp(data->cmd, "unset") == 0)
		exec_unset(data);
	if (((ft_strcmp(data->cmd, "env") == 0)
			|| (ft_strcmp(data->cmd, "ENV") == 0)))
		exec_env();
}

int	is_builtin(t_list *tmp)
{
	t_parse	*data;

	data = tmp->content;
	if ((ft_strcmp(data->cmd, "echo") == 0)
		|| (ft_strcmp(data->cmd, "ECHO") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "pwd") == 0)
		|| (ft_strcmp(data->cmd, "PWD") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "env") == 0)
		|| (ft_strcmp(data->cmd, "ENV") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "cd") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "export") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "unset") == 0))
		return (1);
	return (0);
}
