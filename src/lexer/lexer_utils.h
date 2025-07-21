/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/03 11:48:42 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H
# include "lexer.h"

// =============================================================================
// FONCTIONS INTERNES DE TOKENISATION
// =============================================================================

/**
 * @brief Crée un nouveau token
 * @param value Valeur du token
 * @param type Type du token
 * @return t_token* Nouveau token, NULL si erreur
 */
t_token			*create_token(char *value, t_token_type type);

/**
 * @brief Ajoute un token à la fin de la liste
 * @param list Pointeur vers la tête de liste
 * @param token Token à ajouter
 */
void			add_token(t_token **list, t_token *token);

// =============================================================================
// GESTION DES QUOTES
// =============================================================================

/**
 * @brief Extrait le contenu entre quotes
 * @param input Chaîne d'entrée
 * @param i Pointeur vers l'index actuel
 * @return char* Contenu extrait, NULL si erreur
 */
char			*handle_quotes(char *input, int *i);

/**
 * @brief Vérifie si les quotes sont fermées
 * @param input Chaîne à vérifier
 * @return bool true si quotes fermées, false sinon
 */
bool			is_quote_closed(char *input);

/**
 * @brief Supprime les quotes externes d'une chaîne
 * @param str Chaîne à traiter
 * @return char* Chaîne sans quotes externes
 */
char			*remove_quotes(char *str);

/**
 * @brief Trouve la quote fermante correspondante
 * @param str Chaîne à analyser
 * @param start Position de la quote ouvrante
 * @param quote_char Caractère de quote à chercher
 * @return int Position de la quote fermante, -1 si non trouvée
 */
int				find_closing_quote(char *str, int start, char quote_char);

/**
 * @brief Extrait une sous-chaîne entre deux positions (helper pour quotes)
 * @param str Chaîne source
 * @param start Position de début
 * @param end Position de fin
 * @return char* Sous-chaîne extraite, NULL si erreur
 */
char			*extract_quoted_content(char *str, int start, int end);

// =============================================================================
// RECONNAISSANCE DES OPÉRATEURS
// =============================================================================

/**
 * @brief Détecte si un caractère est un opérateur
 * @param c Caractère à tester
 * @return bool true si opérateur, false sinon
 */
bool			is_operator(char c);

/**
 * @brief Détermine le type d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return t_token_type Type de l'opérateur
 */
t_token_type	get_operator_type(char *str);

/**
 * @brief Calcule la longueur d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return int Longueur de l'opérateur (1 pour <, >, | ; 2 pour >>, <<)
 */
int				get_operator_len(char *str);

// =============================================================================
// UTILITAIRES DE NAVIGATION
// =============================================================================

/**
 * @brief Ignore les espaces dans une chaîne
 * @param str Chaîne à parcourir
 * @param i Pointeur vers l'index actuel
 */
void			skip_whitespace(char *str, int *i);

/**
 * @brief Teste si un caractère est un espace
 * @param c Caractère à tester
 * @return bool true si espace, false sinon
 */
bool			is_whitespace(char c);

/**
 * @brief Compte le nombre de tokens dans une liste (helper debug)
 * @param tokens Liste de tokens
 * @return int Nombre de tokens
 */
int				count_tokens(t_token *tokens);



#endif