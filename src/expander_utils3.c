/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:24:36 by uakkan            #+#    #+#             */
/*   Updated: 2023/10/15 13:37:55 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	quote_build(char **tmp, char **data, int *i, int *j)
{
	char	a;
	int		x;
	int		y;

	x = *i;
	y = *j;
	a = (*tmp)[x++];
	*i += 1;
	while ((*tmp)[x] && (*tmp)[x] != a)
	{
		(*data)[y] = (*tmp)[x++];
		*i += 1;
		*j += 1;
		y++;
	}
}

char	*quote_control(char *tmp)
{
	char	*data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			quote_build(&tmp, &data, &i, &j);
		else
		{
			data[j] = tmp[i];
			j++;
		}
		i++;
	}
	data[j] = '\0';
	return (data);
}

char	*ft_before_dollar_control(char *tmp)
{
	int		i;
	int		x;
	char	*data;

	x = 0;
	i = 0;
	while (tmp[i] && tmp[i++] != '$')
		x++;
	if (x > 0)
	{
		data = ft_substr(tmp, 0, x);
		return (data);
	}
	return (NULL);
}

char	*ft_after_dark(char *str)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	if (str[0] == '$' && str[1] == '?')
		flag = 1;
	while ((str[i] != '$' && str[i + 1] != '?') && str[i] && flag == 0)
		i++;
	if (str[i] && (str[i] == '$' && str[i + 1] == '?') && str[i + 2])
	{
		i += 2;
		tmp = ft_substr(str, i, ft_strlen(str));
		return (tmp);
	}
	return (NULL);
}

void	ft_exit_status(char *tmp, t_list *data)
{
	char	*str;
	char	*str1;
	char	*str2;
	char	*str_tmp;
	int		flag;

	flag = 0;
	str_tmp = NULL;
	str = ft_before_dollar_control(tmp);
	str1 = ft_itoa(g_shell->exec_status);
	str2 = ft_after_dark(tmp);
	free(data->content);
	if (str && str2)
	{
		str_tmp = ft_strjoin(str, str1);
		data->content = ft_strjoin(str_tmp, str2);
	}
	else if (str2)
		data->content = ft_strjoin(str1, str2);
	else if (str)
		data->content = ft_strjoin(str, str1);
	else
		flag = (_ft_exit_status(data, str1), 1);
	free_tmps(str, str2, str_tmp);
	free_str1(str1, flag);
}
