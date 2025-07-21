/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:22:52 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/03 12:16:15 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../../include/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

// Types de tokens pour le lexer
typedef enum e_token_type
{
	TOKEN_CMD,          // Commande (premier mot)
	TOKEN_ARG,          // Argument
	TOKEN_PIPE,         // |
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_EOF           // Fin de chaîne
}		t_token_type;

// Structure de token pour le lexer
typedef struct s_token
{
	char *value;          // Valeur du token (chaîne)
	t_token_type type;    // Type du token
	struct s_token *next; // Pointeur vers le token suivant
}		t_token;

// =============================================================================
// FONCTIONS PUBLIQUES DU LEXER
// =============================================================================

/**
 * @brief Point d'entrée principal du lexer
 * @param input Chaîne d'entrée à tokeniser
 * @return t_token* Liste chaînée de tokens, NULL si erreur
 */
t_token	*lexer(char *input);

/**
 * @brief Libère la mémoire de toute la liste de tokens
 * @param tokens Liste de tokens à libérer
 */
void	free_tokens(t_token *tokens);

#endif