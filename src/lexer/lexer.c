/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:43:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 21:28:06 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"

/**
 * @brief Traite un opérateur et crée le token correspondant
 * @param input Chaîne d'entrée complète
 * @param i Pointeur vers l'index actuel dans la chaîne
 * @return t_token* Token créé pour l'opérateur, NULL si erreur
 */
static t_token	*process_operator(char *input, int *i)
{
	t_token			*token;
	t_token_type	type;
	int				len;
	char			*value;

	type = get_operator_type(&input[*i]);
	len = get_operator_len(&input[*i]);
	value = ft_substr(input, *i, len);
	if (!value)
		return (NULL);
	token = create_token(value, type, 0, 0);
	free(value);
	*i += len;
	return (token);
}

/**
 * @brief Traite un mot (commande ou argument) et crée le token
 * @param input Chaîne d'entrée complète
 * @param i Pointeur vers l'index actuel dans la chaîne
 * @return t_token* Token créé pour le mot, NULL si erreur
 */
static t_token	*process_word(char *input, int *i)
{
	char	*start;
	int		len;
	char	*value;
	t_token	*token;
	char	quote_char;

	start = &input[*i];
	len = 0;
	quote_char = 0;
	while (input[*i])
	{
		if ((input[*i] == '"' || input[*i] == '\'') && !quote_char)
			quote_char = input[*i];
		else if (input[*i] == quote_char)
			quote_char = 0;
		else if (!quote_char && (is_whitespace(input[*i])
				|| is_operator(input[*i])))
			break ;
		(*i)++;
		len++;
	}
	value = ft_substr(start, 0, len);
	if (!value)
		return (NULL);
	token = create_token(value, TOKEN_ARG, 0, 0);
	free(value);
	return (token);
}

/**
 * @brief Convertit le premier token ARG en token CMD
 * @param tokens Pointeur vers la tête de la liste de tokens
 * @note Selon la logique shell, le premier mot est toujours une commande
 */
static void	set_first_token_as_cmd(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_ARG)
		tokens->type = TOKEN_CMD;
}

/**
 * @brief Convertit les tokens ARG après un pipe en tokens CMD
 * @param tokens Pointeur vers la tête de la liste de tokens
 * @note Après un pipe, le prochain mot est une nouvelle commande
 */
static void	set_cmd_after_pipe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE && current->next
			&& current->next->type == TOKEN_ARG)
			current->next->type = TOKEN_CMD;
		current = current->next;
	}
}

/**
 * @brief Point d'entrée principal du lexer
 * @param input Chaîne d'entrée à tokeniser
 * @return t_token* Liste chaînée de tokens, NULL si erreur
 */
t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*new_token;
	int		i;

	head = NULL;
	i = 0;
	if (!input || is_quote_closed(input) > 0)
		return (NULL);
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			new_token = process_operator(input, &i);
		else
			new_token = process_word(input, &i);
		if (!new_token)
			return (free_tokens(head), NULL);
		add_token(&head, new_token);
	}
	set_first_token_as_cmd(head);
	set_cmd_after_pipe(head);
	return (head);
}
