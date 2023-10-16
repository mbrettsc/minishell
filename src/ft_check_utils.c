/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:31:03 by uakkan            #+#    #+#             */
/*   Updated: 2023/10/15 13:40:39 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	get_env_utils(t_list **data, char *tmp, char *tmp2)
{
	char	*tmp3;

	tmp3 = ft_strdup((*data)->content);
	free((*data)->content);
	(*data)->content = quote_control(tmp3);
	free_tmp_tmp2(tmp, tmp2, tmp3);
	(*data) = (*data)->next;
}

int	is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (!cmd[i])
		return (0);
	return (1);
}

int	print_error(void)
{
	printf("%s\n", "minishell: syntax error near unexpected token");
	return (0);
}
