/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/03 00:22:01 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"

/**
 * @brief Extrait le contenu entre quotes
 * @param input Chaîne d'entrée
 * @param i Pointeur vers l'index actuel
 * @return char* Contenu extrait, NULL si erreur
 */
char	*handle_quotes(char *input, int *i)
{
	// TODO: Implementation
	(void)input;
	(void)i;
	return (NULL);
}

/**
 * @brief Vérifie si les quotes sont fermées
 * @param input Chaîne à vérifier
 * @return bool true si quotes fermées, false sinon
 */
bool	is_quote_closed(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (input[i + 1] == '\'')
				i += 2;
			else
				return (false);
		}
	}
	return (false);
}

/**
 * @brief Supprime les quotes externes d'une chaîne
 * @param str Chaîne à traiter
 * @return char* Chaîne sans quotes externes
 */
char	*remove_quotes(char *str)
{
	// TODO: Implementation
	(void)str;
	return (NULL);
}