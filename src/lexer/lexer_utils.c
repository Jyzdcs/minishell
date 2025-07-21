/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 20:39:59 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * @brief Trouve la quote fermante correspondante
 * @param str Chaîne à analyser
 * @param start Position de la quote ouvrante
 * @param quote_char Caractère de quote à chercher
 * @return int Position de la quote fermante, -1 si non trouvée
 */
int	find_closing_quote(char *str, int start, char quote_char)
{
	(void)str;
	(void)start;
	(void)quote_char;
	return (-1);
}

/**
 * @brief Extrait une sous-chaîne entre deux positions (helper pour quotes)
 * @param str Chaîne source
 * @param start Position de début
 * @param end Position de fin
 * @return char* Sous-chaîne extraite, NULL si erreur
 */
char	*extract_quoted_content(char *str, int start, int end)
{
	(void)str;
	(void)start;
	(void)end;
	return (NULL);
}

/**
 * @brief Compte le nombre de tokens dans une liste (helper debug)
 * @param tokens Liste de tokens
 * @return int Nombre de tokens
 */
int	count_tokens(t_token *tokens)
{
	(void)tokens;
	return (0);
}

/**
 * @brief Libère la mémoire de toute la liste de tokens
 * @param tokens Liste de tokens à libérer
 */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
