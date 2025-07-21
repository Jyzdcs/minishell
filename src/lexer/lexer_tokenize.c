/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 20:37:47 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * @brief Crée un nouveau token
 * @param value Valeur du token
 * @param type Type du token
 * @param quoted 1 si le token est entre quotes, 0 sinon
 * @param expand 1 si le token contient au moins un $, 0 sinon
 * @return t_token* Nouveau token, NULL si erreur
 */
t_token	*create_token(char *value, t_token_type type, int quoted, int expand)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->quoted = quoted;
	new_token->expand = expand;
	new_token->next = NULL;
	return (new_token);
}

/**
 * @brief Ajoute un token à la fin de la liste
 * @param list Pointeur vers la tête de liste
 * @param token Token à ajouter
 */
void	add_token(t_token **list, t_token *token)
{
	t_token	*current;

	if (!token)
		return ;
	if (!*list)
	{
		*list = token;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = token;
}
