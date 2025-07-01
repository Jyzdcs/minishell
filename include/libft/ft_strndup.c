/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:58:49 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/26 18:03:35 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*cp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	cp = malloc(sizeof(char) * n + 1);
	if (cp == NULL)
		return (NULL);
	while (i < len && i < n)
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
