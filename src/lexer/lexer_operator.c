/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/03 00:00:48 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Détecte si un caractère est un opérateur
 * @param c Caractère à tester
 * @return bool true si opérateur, false sinon
 */
bool	is_operator(char c)
{
	// TODO: Implementation
	(void)c;
	return (false);
}

/**
 * @brief Détermine le type d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return t_token_type Type de l'opérateur
 */
t_token_type	get_operator_type(char *str)
{
	// TODO: Implementation
	(void)str;
	return (TOKEN_EOF);
}

/**
 * @brief Calcule la longueur d'un opérateur
 * @param str Chaîne contenant l'opérateur
 * @return (int Longueur de l'opérateur (1 pour <, >, |); 2 pour >>, <<)
 */
int	get_operator_len(char *str)
{
	// TODO: Implementation
	(void)str;
	return (0);
}