/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:23:06 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/10/15 18:14:39 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_list *tmp, int *fd, int fd_index)
{
	int	control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(tmp, fd, fd_index);
	else
		exec_others(tmp, env, fd, fd_index);
	free_();
	free_loop(1);
	free(g_shell->lex_list);
	free(g_shell);
	exit(0);
}

void	run_single_command(char **env, t_list *data)
{
	int	control;

	control = is_builtin(data);
	if (control)
		execute_builtin_command(g_shell->parse, NULL, -1);
	else
		exec_others(g_shell->parse, env, NULL, -1);
}

void	_multi_command(t_parse **data, t_list **tmp)
{
	if ((*data)->infile > STDERR || (*data)->outfile > STDERR
		|| (*data)->type == HEREDOC)
		(*tmp) = (*tmp)->next->next;
	else
		(*tmp) = (*tmp)->next;
}

void	multi_command(char **env, int x, t_list	*tmp)
{
	int		*fd;
	t_parse	*data;

	fd = create_pipe();
	while (tmp)
	{
		data = tmp->content;
		switch_pipe(&fd);
		pipe(&fd[2]);
		data->pid = fork();
		if (x++ == 0)
			data->control = 1;
		if (data->pid == 0)
			run_command(env, tmp, fd, 2);
		_multi_command(&data, &tmp);
		if (fd[4] && fd[5])
		{
			close(fd[4]);
			close(fd[5]);
			fd[4] = 0;
			fd[5] = 0;
		}
	}
	clear_pipe(fd);
	wait_all();
}

void	exec(char **env)
{
	int		x;
	t_list	*tmp;
	t_parse	*parse;

	tmp = g_shell->parse;
	parse = tmp->content;
	if (g_shell->does_have_heredoc != 0)
		loop_heredoc();
	if (!ft_strcmp(g_shell->cmd, ""))
		return ;
	if (ft_strcmp(parse->cmd, "exit") == 0 && g_shell->does_have_heredoc != -10)
	{
		free_();
		free_loop(1);
		free(g_shell->lex_list);
		free(g_shell);
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	x = single_or_multi_command();
	if (!x && g_shell->does_have_heredoc != -10)
		run_single_command(env, g_shell->parse);
	else if (g_shell->does_have_heredoc != -10)
		multi_command(env, 0, g_shell->parse);
	g_shell->does_have_heredoc = 0;
}
