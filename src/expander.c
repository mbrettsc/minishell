/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:45:04 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/07/23 01:45:11 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_tilde(char *tmp, char *str, t_list *data)
{
	int		y;
	int		i;
	int		j;
	char	*key;

	j = 0;
	y = 0;
	i = 0;
	key = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (ft_strchr(tmp, '/'))
	{
		tmp = ft_strchr(tmp, '/');
		y++;
	}
	while (str[i])
	{
		key[j] = str[i++];
		j++;
	}
	key[j] = '\0';
	if (y == 1)
		ft_tilde_build1(data, key, tmp);
	else
		ft_tilde_build2(data, str);
	free(key);
}

int	check_env(t_list *data, char *tmp, int i)
{
	t_env	*y;
	char	*x;
	t_list	*shell_data;

	shell_data = g_shell->env;
	x = ft_strdup((char *)data->content);
	while (shell_data)
	{
		y = shell_data->content;
		if (tmp[i] == '~' && ft_strcmp(y->key, "HOME") == 0)
			ft_tilde(tmp, y->value, data);
		if (tmp[i] == '$' && tmp[i + 1] == '?')
			ft_exit_status(tmp, data);
		else if (tmp[i] == '$' && ft_isdigit(tmp[i + 1]) && tmp[i + 2])
			get_after_num(tmp, data, i + 2);
		else if (tmp[i] == '$')
			does_dollar_make_sense(tmp, data, shell_data, i + 1);
		shell_data = shell_data->next;
	}
	if (!ft_strcmp(x, (char *)data->content))
		erase_after(tmp, data, i + 1);
	free(x);
	return (0);
}

void	_get_env_to_lexlist(char **tmp, int i, t_list **data)
{
	free(*tmp);
	(*tmp) = ft_strdup((*data)->content);
	if (((*tmp)[i] == '~') && ((*tmp)[0] != '\'' || (*tmp)[0] != '\"')
		&& ((*tmp)[i + 1] == '/' || !(*tmp)[i + 1]))
	{
		if (i >= 1)
		{
			if (!ft_isprint((*tmp)[i - 1]))
				check_env(*data, *tmp, i);
		}
		else
			check_env(*data, *tmp, i);
	}
}

void	get_env_to_lexlist(t_lexer **lex_list)
{
	t_list	*data;
	char	*tmp;
	char	*tmp2;
	int		i;

	data = (*lex_list)->lex;
	while (data)
	{
		i = 0;
		tmp2 = ft_strdup(data->content);
		tmp = quote_control(tmp2);
		while (tmp[i])
		{
			_get_env_to_lexlist(&tmp, i, &data);
			if (tmp[i] == '$' && tmp[0] != '\'')
			{
				check_env(data, tmp, i);
				if (!ft_strcmp(data->content, ""))
					break ;
			}
			i++;
		}
		free_tmp_tmp2(tmp, tmp2);
		(data) = (data)->next;
	}
}

void	expander(void)
{
	if (ft_strcmp(g_shell->cmd, ""))
		get_env_to_lexlist(&(g_shell->lex_list));
}
