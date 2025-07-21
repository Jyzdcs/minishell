/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:43:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 16:42:50 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"

t_token	*lexer(char *input)
{
	t_token *tokens;

	tokens = NULL;
	if (!input)
		return (tokens);
	if (!is_quote_closed(input))
		return (tokens);

	// Pour l'instant, retournons un token factice pour tester
	// que tout fonctionne correctement
	tokens = create_token("test", TOKEN_CMD);
	return (tokens);
}