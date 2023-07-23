/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_or_multi_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uakkan <uakkan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:53:50 by uakkan            #+#    #+#             */
/*   Updated: 2023/07/19 19:55:00 by uakkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_or_multi_command(void)
{
	t_list	*tmp;
	t_parse	*data;

	tmp = g_shell->parse;
	data = g_shell->parse->content;
	while (tmp)
	{
		data = tmp->content;
		if (data->type == 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
