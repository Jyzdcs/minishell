/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 21:37:52 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "expander_utils.h"

/**
 * @brief Détermine le type de quote à une position
 * @param str Chaîne à analyser
 * @param pos Position à vérifier
 * @return char Type de quote ('\'', '"', ou 0 si aucune)
 */
char	get_quote_type(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (0);
}

/**
 * @brief Trouve la quote fermante correspondante
 * @param str Chaîne à analyser
 * @param start Position de la quote ouvrante
 * @param quote_type Type de quote à chercher
 * @return int Position de la quote fermante, -1 si non trouvée
 */
int	find_closing_quote(char *str, int start, char quote_type)
{
	(void)str;
	(void)start;
	(void)quote_type;
	return (-1);
}