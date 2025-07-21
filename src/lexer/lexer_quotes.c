/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 20:26:32 by kclaudan         ###   ########.fr       */
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
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'')
			(*i)++;
	}
	else if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"')
			(*i)++;
	}
	return (NULL);
}

/**
 * @brief Vérifie si les quotes sont fermées
 * @param input Chaîne à vérifier
 * @return bool true si quotes fermées, false sinon
 */
int	is_quote_closed(char *input)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote + in_double_quote);
}

/**
 * @brief Supprime les quotes externes d'une chaîne
 * @param str Chaîne à traiter
 * @return char* Chaîne sans quotes externes
 */
char	*remove_quotes(char *str)
{
	if (!str)
		return (NULL);
	if (str[0] == '\'')
		return (ft_strtrim(str + 1, "\'"));
	if (str[0] == '"')
		return (ft_strtrim(str + 1, "\""));
	return (str);
}
