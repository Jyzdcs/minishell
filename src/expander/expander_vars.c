/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 21:37:39 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "expander_utils.h"

/**
 * @brief Extrait le nom d'une variable depuis $VAR
 * @param str Chaîne contenant $VAR
 * @param start Index du caractère $
 * @return char* Nom de la variable, NULL si erreur
 */
char	*extract_var_name(char *str, int start)
{
	(void)str;
	(void)start;
	return (NULL);
}

/**
 * @brief Trouve la prochaine occurrence de $ dans une chaîne
 * @param str Chaîne à analyser
 * @param start Position de début de recherche
 * @return int Index du $, -1 si non trouvé
 */
int	find_next_dollar(char *str, int start)
{
	(void)str;
	(void)start;
	return (-1);
}

/**
 * @brief Vérifie si $ est dans une zone d'expansion autorisée
 * @param str Chaîne complète
 * @param pos Position du $ à vérifier
 * @return bool true si expansion autorisée, false sinon
 */
bool	is_expandable_context(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (0);
}