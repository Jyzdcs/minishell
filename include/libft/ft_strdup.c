/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:15:17 by kclaudan          #+#    #+#             */
/*   Updated: 2024/10/26 14:15:17 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	cp = malloc(sizeof(char) * len + 1);
	if (cp == NULL)
		return (NULL);
	while (i < len)
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	(void)ac;
	const char *str = "SALUT";
	char *cp = ft_strdup(str);
	printf("%s\n", cp);
}*/