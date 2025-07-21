/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 16:42:40 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (!in_single_quote && !in_double_quote);
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