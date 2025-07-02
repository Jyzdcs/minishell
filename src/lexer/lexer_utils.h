/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:04 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "lexer.h"

/*
** =============================================================================
** UTILITAIRES SPÉCIFIQUES AU LEXER
** =============================================================================
*/

/**
 * @brief Trouve la quote fermante correspondante
 * @param str Chaîne à analyser
 * @param start Position de la quote ouvrante
 * @param quote_char Caractère de quote à chercher
 * @return int Position de la quote fermante, -1 si non trouvée
 */
int		find_closing_quote(char *str, int start, char quote_char);

/**
 * @brief Extrait une sous-chaîne entre deux positions (helper pour quotes)
 * @param str Chaîne source
 * @param start Position de début
 * @param end Position de fin
 * @return char* Sous-chaîne extraite, NULL si erreur
 */
char	*extract_quoted_content(char *str, int start, int end);

/**
 * @brief Compte le nombre de tokens dans une liste (helper debug)
 * @param tokens Liste de tokens
 * @return int Nombre de tokens
 */
int		count_tokens(t_token *tokens);

/**
 * @brief Ignore les espaces dans une chaîne
 * @param str Chaîne à parcourir
 * @param i Pointeur vers l'index actuel
 */
void	skip_whitespace(char *str, int *i);

/**
 * @brief Teste si un caractère est un espace
 * @param c Caractère à tester
 * @return bool true si espace, false sinon
 */
bool	is_whitespace(char c);

/**
 * @brief Libère la mémoire de toute la liste de tokens
 * @param tokens Liste de tokens à libérer
 */
void	free_tokens(t_token *tokens);

#endif 