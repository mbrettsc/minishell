/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:00 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/20 18:32:24 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	edit_env(t_list *node, char *key, char *value)
{
	t_env	*new_env;
	t_env	*env;

	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			free(value);
			free(key);
			return ;
		}
		node = node->next;
	}
	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(g_shell->env), ft_lstnew(new_env));
	}
}

void	declare_export(void *data)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = g_shell->parse->content;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_export(t_parse *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (data->text == NULL)
		ft_lstiter(g_shell->env, declare_export);
	else if (!ft_strchr(data->text[0], '='))
		return ;
	else
	{
		while (data->text[i])
		{
			key = ft_substr(data->text[i], 0,
					ft_strchrindex(data->text[i], '='));
			value = ft_substr(data->text[i],
					ft_strchrindex(data->text[i], '=') + 1,
					(ft_strlen(data->cmd) - 1));
			edit_env(g_shell->env, key, value);
			i++;
		}
	}
	g_shell->exec_status = 0;
}

int	unset_edit(t_env *env, t_list **node, t_list **prev_node, char *key)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (ft_strcmp(env->key, key) == 0)
	{
		if (prev_node == NULL)
			g_shell->env = (*node)->next;
		else
			(*prev_node)->next = (*node)->next;
		free(tmp->key);
		free(tmp->value);
		free((*node)->content);
		free(*node);
		return (1);
	}
	return (0);
}

void	exec_unset(t_parse *data)
{
	int		i;
	int		x;
	char	*key;
	t_list	*prev_node;
	t_list	*node;

	i = 0;
	key = NULL;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		key = data->text[i];
		prev_node = NULL;
		node = g_shell->env;
		while (node != NULL)
		{
			x = unset_edit((t_env *)node->content, &node, &prev_node, key);
			if (x)
				break ;
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
