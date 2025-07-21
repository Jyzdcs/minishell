/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 21:37:23 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

/**
 * @brief Calcule la taille finale après expansion (pour malloc)
 * @param str Chaîne originale
 * @param env Tableau d'environnement
 * @param last_status Code de retour actuel
 * @return int Taille nécessaire en octets
 */
int	calculate_expanded_size(char *str, char **env, int last_status)
{
	(void)str;
	(void)env;
	(void)last_status;
	return (0);
}

/**
 * @brief Vérifie si on est dans des quotes simples à une position
 * @param str Chaîne complète
 * @param pos Position à vérifier
 * @return bool true si dans quotes simples, false sinon
 */
bool	is_in_single_quotes(char *str, int pos)
{
	(void)str;
	(void)pos;
	return (0);
}

/**
 * @brief Construit une nouvelle chaîne avec remplacement de variable
 * @param original Chaîne originale
 * @param var_start Position de début de $VAR
 * @param var_end Position de fin de $VAR
 * @param replacement Valeur de remplacement
 * @return char* Nouvelle chaîne, NULL si erreur
 */
char	*build_expanded_string(char *original, int var_start, int var_end,
		char *replacement)
{
	(void)original;
	(void)var_start;
	(void)var_end;
	(void)replacement;
	return (NULL);
}

/**
 * @brief Convertit un entier en chaîne pour $?
 * @param status Code de retour à convertir
 * @return char* Chaîne représentant le nombre, NULL si erreur
 */
char	*status_to_string(int status)
{
	(void)status;
	return (NULL);
}

/**
 * @brief Vérifie si un caractère est valide dans un nom de variable
 * @param c Caractère à tester
 * @return bool true si valide (alphanumériques + _), false sinon
 */
bool	is_valid_var_char(char c)
{
	(void)c;
	return (0);
}