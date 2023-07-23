/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:07:54 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/07/20 01:09:55 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

t_shell	*g_shell;

void	shell_init(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	(*shell)->env = malloc(sizeof(t_env));
	(*shell)->lex_list = malloc(sizeof(t_lexer));
	(*shell)->lex_list->lex = NULL;
	(*shell)->does_have_heredoc = 0;
	(*shell)->exec_status = 0;
	(*shell)->heredoc = NULL;
	(*shell)->cmd = NULL;
}

void	get_readline(void)
{
	g_shell->cmd = readline("minishell-$ ");
	if (!g_shell->cmd)
	{
		free_loop(0);
		free_();
		free(g_shell->lex_list);
		free(g_shell);
		exit(1);
	}
	add_history(g_shell->cmd);
}

void	go_parser(char **env)
{
	if (ft_strcmp(g_shell->cmd, ""))
	{
		if (ft_parser())
			exec(env);
	}
}

void	error_free(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_node((*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	int		control;

	(void)av;
	control = 0;
	if (ac != 1)
		exit(printf("This program cannot accept any arguments\n"));
	shell_init(&g_shell);
	env_get(env, &g_shell);
	signals_control();
	while (1)
	{
		get_readline();
		if (quote_check(g_shell->cmd))
		{
			lexer();
			expander();
			control = check();
			if (control)
				go_parser(env);
			else
				error_free(&(g_shell->lex_list)->lex);
		}
		free_loop(control);
	}
}
