/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:56 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 01:01:45 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	killer(int sig)
{
	(void)sig;
	free_();
	free_loop(1);
	free(g_shell->lex_list);
	free(g_shell);
	write(1, "\n", 1);
	exit(1);
}

void	set_heredoc(int sig)
{
	(void)sig;
	g_shell->does_have_heredoc = -10;
}
