/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:19:59 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/26 12:27:23 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand(char *str)
{
	int		i;
	char	new;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && till_sep(str, ' '))
		{
			
		}
	}
}
