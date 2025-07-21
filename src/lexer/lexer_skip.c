/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 20:38:47 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * @brief Ignore les espaces dans une chaîne
 * @param str Chaîne à parcourir
 * @param i Pointeur vers l'index actuel
 */
void	skip_whitespace(char *str, int *i)
{
	while (str[*i] && is_whitespace(str[*i]))
		(*i)++;
}

/**
 * @brief Teste si un caractère est un espace
 * @param c Caractère à tester
 * @return int 1 si espace, 0 sinon
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == '\0');
}
