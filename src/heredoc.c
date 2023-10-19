/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:23:11 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/10/15 13:37:06 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

char	*add_char(char *str, char a)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	if (!a)
	{
		free(tmp);
		return (NULL);
	}
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = a;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}

void	get_var(int *fd)
{
	char	*a;

	a = malloc(sizeof(char));
	if (!a)
	{
		g_shell->heredoc = NULL;
		return ;
	}
	if (g_shell->heredoc)
		free(g_shell->heredoc);
	g_shell->heredoc = ft_calloc(sizeof(char), 2);
	while (read(fd[0], a, 1))
	{
		g_shell->heredoc = add_char(g_shell->heredoc, *a);
		free(a);
		a = malloc(sizeof(char));
	}
	if (a)
		free(a);
	close(fd[0]);
}

void	get_input(t_list *tmp, int *fd)
{
	char	*delimiter;
	char	*buffer;
	t_parse	*parse_list;

	parse_list = tmp->next->content;
	delimiter = parse_list->text[0];
	while (1)
	{
		buffer = readline("> ");
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			if (buffer)
				free(buffer);
			break ;
		}
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		if (buffer)
			free(buffer);
	}
}

void	heredoc(t_list *tmp)
{
	int		fd[2];
	int		id;

	pipe(fd);
	signal(SIGINT, set_heredoc);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, killer);
		close(fd[0]);
		get_input(tmp, fd);
		close(fd[1]);
		free_();
		free_loop(1);
		free(g_shell->lex_list);
		free(g_shell);
		exit(1);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, signals);
	close(fd[1]);
	get_var(fd);
}

void	loop_heredoc(void)
{
	t_list	*tmp;
	t_parse	*parse_list;

	tmp = g_shell->parse;
	while (tmp)
	{
		parse_list = tmp->content;
		if (parse_list->type == HEREDOC)
			heredoc(tmp);
		tmp = tmp->next;
	}
}
