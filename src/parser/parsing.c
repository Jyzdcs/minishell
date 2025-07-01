/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:55:17 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/30 19:24:35 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_sep(char *str)
{
	if (str[0] != '|' && str[0] != '<' && str[0] != '>'
			&& ft_strncmp(str, "<<", ft_strlen(str))
			&& ft_strncmp(str, ">>", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "<<", ft_strlen(str))
			|| !ft_strncmp(str, ">>", ft_strlen(str)))
		return (2);
	return (1);
}

int	parts_nb(char *prompt)
{
	int	parts;
	int	counter;
	int	i;

	parts = 0;
	counter = 0;
	i = 0;
	while (prompt[i])
	{
		if (!is_sep(prompt + i) && counter == 0)
		{
			parts++;
			counter = 1;
		}
		else if (is_sep((prompt + i)))
		{
			parts++;
			counter = 1;
			if (!ft_strncmp(prompt + i, "<<", ft_strlen(prompt + i))
				|| !ft_strncmp(prompt + i, ">>", ft_strlen(prompt + i)))
				i++;
		}
		i++;
	}
	return (parts);
}

void	splitting(char *prompt, char **result, int size)
{
	int	i;
	int	j;
	int	parts;

	i = 0;
	j = 0;
	parts = 0;
	while (parts < size && prompt[i])
	{
		while(prompt[i] && !is_sep(prompt))
			i++;
		result[parts] = ft_strndup(prompt + j, i - j);
		if (!result[parts])
			return (free_arr(result, parts));
		if (is_sep(prompt + i) == 2)
			result[++parts] = ft_strndup(prompt + i++, 2);
		else if (is_sep(prompt + i) == 1)
			result[++parts] = ft_strndup(prompt + i, 1);
		if (!result[parts])
			return (free_arr(result, parts));
		j = i++;
	}
}

char	**cmnd_split(char *prompt, t_line *ligne)
{
	char	**result;
	int		parts;

	parts = parts_nb(prompt);
	ligne->cmnd_size = parts;
	result = malloc(sizeof(char *) * parts);
	if (!result)
		return (NULL);
	splitting(prompt, result, parts);
	for (int i = 0; i < parts; i++)
		printf("%s\n", result[i]);
	return (result);
}

char **parse_prompt(char *prompt, t_line *ligne)
{
	prompt = expand(prompt);
	if (!prompt)
		return (NULL);
	printf("%s\n", prompt);
	return (cmnd_split(prompt, ligne));
}
