/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:22:52 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:12 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// Types de tokens pour le lexer
typedef	enum	e_token_type
{
	TOKEN_CMD,			// Commande (premier mot)
	TOKEN_ARG,			// Argument
	TOKEN_PIPE,			// |
	TOKEN_REDIR_IN,		// <
	TOKEN_REDIR_OUT,	// >
	TOKEN_REDIR_APPEND,	// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF			// Fin de chaîne
}							t_token_type;

// Structure de token pour le lexer
typedef struct	s_token
{
	char				*value;			// Valeur du token (chaîne)
	t_token_type		type;			// Type du token
	struct s_token		*next;			// Pointeur vers le token suivant
}				t_token;

// =============================================================================
// FONCTIONS DE TOKENISATION
// =============================================================================

/**
 * @brief Point d'entrée principal du lexer
 * @param input Chaîne d'entrée à tokeniser
 * @return t_token* Liste chaînée de tokens, NULL si erreur
 */
t_token	*lexer(char *input);

/**
 * @brief Crée un nouveau token
 * @param value Valeur du token
 * @param type Type du token
 * @return t_token* Nouveau token, NULL si erreur
 */
t_token	*create_token(char *value, t_token_type type);

/**
 * @brief Ajoute un token à la fin de la liste
 * @param list Pointeur vers la tête de liste
 * @param token Token à ajouter
 */
void	add_token(t_token **list, t_token *token);

// =============================================================================
// GESTION DES QUOTES
// =============================================================================

/**
 * @brief Extrait le contenu entre quotes
 * @param input Chaîne d'entrée
 * @param i Pointeur vers l'index actuel
 * @return char* Contenu extrait, NULL si erreur
 */
char	*handle_quotes(char *input, int *i);

/**
 * @brief Vérifie si les quotes sont fermées
 * @param input Chaîne à vérifier
 * @return bool true si quotes fermées, false sinon
 */
bool	is_quote_closed(char *input);

/**
 * @brief Supprime les quotes externes d'une chaîne
 * @param str Chaîne à traiter
 * @return char* Chaîne sans quotes externes
 */
char	*remove_quotes(char *str);

// =============================================================================
// RECONNAISSANCE DES OPÉRATEURS
// =============================================================================

/**
 * @brief Détecte si un caractère est un opérateur
 * @param c Caractère à tester
 * @return bool true si opérateur, false sinon
 */
bool	is_operator(char c);

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
int		get_operator_len(char *str);

#endif