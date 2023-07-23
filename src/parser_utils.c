/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:52 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 17:19:07 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parse_init(void)
{
	(g_shell)->parse = malloc(sizeof(t_list));
	(g_shell)->parse->content = NULL;
	(g_shell)->parse->next = NULL;
}

t_parse	*parse_(int *j, t_list *new, int *i)
{
	t_parse	*parse;
	char	*str;

	str = new->content;
	parse = malloc(sizeof(t_parse));
	if (parse)
	{
		parse->cmd = NULL;
		parse->text = ft_calloc(sizeof(char *), (size_t)ft_lstsize(new) + 1);
		parse->type = 0;
		*j = 0;
		if (new && str[0] == '|' && *i == 0)
			parse->cmd = ft_strdup(new->next->content);
		else if (new && *i == 0)
			parse->cmd = ft_strdup(new->content);
		parse->infile = STDINN;
		parse->outfile = STDOUT;
		parse->fd = 1;
		parse->pid = 0;
		parse->control = 0;
	}
	return (parse);
}

void	tokenize_type(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_shell->does_have_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

void	get_text_utils(char **tmp, t_parse ***parse, int j, int k)
{
	(*tmp)[k] = '\0';
	(**parse)->text[j] = *tmp;
	(**parse)->text[j + 1] = NULL;
}

void	get_text(t_parse **parse, char *str, int j, int a)
{
	int		i;
	int		k;
	char	*tmp;
	int		size;

	i = 0;
	k = 0;
	size = 0;
	if (str)
		size = ft_strlen(str);
	tmp = malloc(sizeof(char) * (size + 1));
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			a = str[i++];
		while (str[i] != a && str[i])
		{
			tmp[k] = str[i];
			i += (++k, 1);
			if (str[i] == a && !str[i + 1])
				a = (++i, 2);
		}
	}
	get_text_utils(&tmp, &parse, j, k);
}
