/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/03 00:00:23 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Crée un nouveau token
 * @param value Valeur du token
 * @param type Type du token
 * @return t_token* Nouveau token, NULL si erreur
 */
t_token	*create_token(char *value, t_token_type type)
{
	// TODO: Implementation
	(void)value;
	(void)type;
	return (NULL);
}

/**
 * @brief Ajoute un token à la fin de la liste
 * @param list Pointeur vers la tête de liste
 * @param token Token à ajouter
 */
void	add_token(t_token **list, t_token *token)
{
	// TODO: Implementation
	(void)list;
	(void)token;
}