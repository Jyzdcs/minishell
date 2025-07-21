/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 20:37:44 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * @brief Détecte si un caractère est un opérateur
 * @param c Caractère à tester
 * @return bool true si opérateur, false sinon
 */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Détermine le type d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return t_token_type Type de l'opérateur
 */
t_token_type	get_operator_type(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strncmp(str, "<", 1) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(str, ">", 1) == 0)
		return (TOKEN_REDIR_OUT);
	return (TOKEN_PIPE);
}

/**
 * @brief Calcule la longueur d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return (int Longueur de l'opérateur (1 pour <, >, |); 2 pour >>, <<)
 */
int	get_operator_len(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	return (1);
}
