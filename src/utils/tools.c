/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:00:45 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/30 19:11:07 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	till_sep(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] && str[i] != ' ' && str[i] != '$'
			&& str[i] != '\'' && str[i] != '\"' && str[i] != '=')
		i++;
	return (i);
}

char	*var_name(char *str)
{
	char	*name;

	name = ft_strndup(str + 1, till_sep(str + 1));
	if (!name)
		return (NULL);
	return (name);
}

void	free_arr(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
