/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_to_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:38 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 17:19:24 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parse_if(t_list *new, t_parse **parse)
{
	if (!new->next && g_shell->parse->content == NULL)
		g_shell->parse->content = (*parse);
	else if (g_shell->parse->content != NULL && !new->next)
		(*parse)->text = (free((*parse)->text), \
	ft_lstadd_back(&(g_shell->parse), ft_lstnew((*parse))), NULL);
}

void	parse_else_if(t_parse **parse, t_list *new, char *str, int *j)
{
	get_text(&(*parse), str, *j, 2); 
	*j += 1;
	if (!new->next)
	{
		if (g_shell->parse->content == NULL)
			g_shell->parse->content = (*parse);
		else
			ft_lstadd_back(&(g_shell->parse), ft_lstnew((*parse)));
	}
}

void	parse_else(t_parse *parse, int *i, char *str)
{
	if (g_shell->parse->content == NULL)
		g_shell->parse->content = parse;
	else
		ft_lstadd_back(&(g_shell->parse), ft_lstnew(parse));
	if (str[0] == '|')
		*i = 0;
}

void	welcome_to_parse(t_list	*node, int i, int j, int flag)
{
	t_list	*new;
	t_parse	*parse;
	char	*str;

	new = (parse_init(), node);
	parse = parse_(&j, new, &i);
	if (ft_lstsize(new) == 1)
		parse->text = (free(parse->text), NULL);
	while (new)
	{
		str = new->content;
		if (i++ == 0 && !(str[0] == '<' && str[1] == '<'))
			parse_if(new, &parse);
		else if ((!ft_strcmp(str, "")) || (str[0] != '|' && (str[0] != '>'
					&& str[1] != '>') && str[0] != '>'
				&& (str[0] != '<' && str[1] != '<') && str[0] != '<'))
			flag = (parse_else_if(&parse, new, str, &j), 1);
		else 
		{
			if (tokenize_type(&parse, str), flag == 0)
				parse->text = (free(parse->text), NULL);
			parse = (parse_else(parse, &i, str), parse_(&j, new, &i));
		}
		new = new->next;
	}
}
