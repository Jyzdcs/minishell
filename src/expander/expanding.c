/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:19:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/28 17:04:07 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*new_str(char *old, char *val, int start, int end)
{
	char	*new;
	int		size;
	int		val_len;
	int		name_len;

	val_len = 0;
	name_len = till_sep(old + start + 1);
	if (val)
		val_len = ft_strlen(val);
	size = start + val_len + end;
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, old, start + 1);
	if (val_len > 0 && start)
		ft_strlcat(new, val, size + 1);
	else if (val_len > 0)
		ft_strlcpy(new, val, size + 1);
	if (start || val_len)
		ft_strlcat(new, old + start + name_len + 1, size + 1);
	else
		ft_strlcpy(new, old + name_len + 1, size + 1);
	return (free(old), new);
}

char	*replace_value(char *old, char *val)
{
	int		i;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (old[start])
	{
		if (old[start] == '$' && till_sep(old + start + 1))
			break ;
		start++;
	}
	if (!old[start])
		return (old);
	i = start + till_sep(old + start + 1) + 1;
	while (old[i++])
		end++;
	return (new_str(old, val, start, end));
}

char	*expand(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && till_sep(str + i + 1))
		{
			var = var_name(str + i);
			if (!var)
				return (NULL);
			str = replace_value(str, getenv(var));
			free(var);
			if (!str)
				return (NULL);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}
