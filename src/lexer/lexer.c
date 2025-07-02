/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:43:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:54:57 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *input)
{
	t_token *tokens;

	tokens = NULL;
	if (!input)
		return (tokens);
	if (is_quote_closed(input))
		return (tokens);
	return (tokens);
}