/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:18 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 18:47:42 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_lexer(void)
{
	t_list	*data;
	t_list	*tmp;

	data = g_shell->lex_list->lex;
	while (data)
	{
		tmp = data;
		data = data->next;
		if (tmp->content)
		{
			if (tmp->content)
				free(tmp->content);
			free(tmp);
		}
	}
}

void	free_text(char **text)
{
	int	i;

	i = 0;
	if (text)
	{
		if (text[i])
		{
			while (text[i])
				free(text[i++]);
		}
		free(text);
	}
}

void	_free_parse(t_list *tmp2)
{
	t_parse	*tmp;

	while (tmp2)
	{
		tmp = tmp2->content;
		if (tmp2->content)
		{
			if (tmp->cmd)
				free(tmp->cmd);
			if (tmp->text)
				free_text(tmp->text);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
	while (g_shell->parse)
	{
		tmp2 = g_shell->parse;
		g_shell->parse = g_shell->parse->next;
		if (tmp2)
			free(tmp2);
	}
}

void	free_parser(void)
{
	t_list	*tmp2;

	tmp2 = g_shell->parse;
	if (tmp2 && tmp2->content)
		_free_parse(tmp2);
	else if (g_shell->parse && !g_shell->parse->content)
		free(g_shell->parse);
}

int	*create_pipe(void)
{
	int	index;
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}
