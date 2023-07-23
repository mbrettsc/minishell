/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:35:57 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/07/20 01:11:13 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	is_valid_other(char *a, char *b)
{
	if ((a[0] == '<' && !a[1]) && !b)
		return (0);
	else if ((a[0] == '>' && !a[1]) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && !a[1])) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '>' && a[1] == '>')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] != '<'))
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] != '>')
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if (((a[0] == '<' && a[1] == '<'))
		&& (b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] == '>')
		&& (b[0] == '<' || b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '|' && !a[1] && b[0] == '|' && !b[1]))
		return (0);
	return (1);
}

int	cmd_is_valid(t_lexer *lex_list)
{
	t_list	*tmp;
	char	*a;
	char	*b;
	int		i;

	i = 0;
	b = NULL;
	a = NULL;
	tmp = lex_list->lex;
	while (tmp)
	{
		a = tmp->content;
		if (tmp->next)
			b = tmp->next->content;
		if ((a[0] == '|' && !a[1]) && i == 0)
			return (print_error());
		else if ((a[0] == '>' && !a[1]) && !b)
			return (print_error());
		else
			if (!is_valid_other(a, b))
				return (print_error());
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	quote_len1(char *data)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
			j++;
		i++;
	}
	return (j);
}

int	quote_check(char *data)
{
	int	x;

	x = 0;
	x = quote_len1(data);
	if (x % 2 != 0)
	{
		printf("minishell: quote error\n");
		return (0);
	}
	return (1);
}

int	check(void)
{
	return (cmd_is_valid(g_shell->lex_list));
}
