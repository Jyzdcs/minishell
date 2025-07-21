/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/21 21:37:07 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "expander_utils.h"

/**
 * @brief Point d'entrée principal de l'expander
 * @param tokens Liste chaînée de tokens à expander
 * @param env Tableau d'environnement
 * @param last_status Code de retour de la dernière commande
 * @return int 0 si succès, -1 si erreur
 */
int	expand_tokens(t_token *tokens, char **env, int last_status)
{
	(void)tokens;
	(void)env;
	(void)last_status;
	return (0);
}

/**
 * @brief Expanse les variables d'un token unique
 * @param token Token à traiter
 * @param env Tableau d'environnement
 * @param last_status Code de retour de la dernière commande
 * @return int 0 si succès, -1 si erreur
 */
int	expand_token(t_token *token, char **env, int last_status)
{
	(void)token;
	(void)env;
	(void)last_status;
	return (0);
}

/**
 * @brief Recherche une variable dans l'environnement
 * @param var_name Nom de la variable à chercher
 * @param env Tableau d'environnement
 * @return char* Valeur de la variable, NULL si inexistante
 */
char	*get_env_value(char *var_name, char **env)
{
	(void)var_name;
	(void)env;
	return (NULL);
}

/**
 * @brief Remplace $VAR par sa valeur dans une chaîne
 * @param str Chaîne à traiter
 * @param env Tableau d'environnement
 * @param last_status Code de retour pour $?
 * @return char* Nouvelle chaîne avec substitutions, NULL si erreur
 */
char	*substitute_vars(char *str, char **env, int last_status)
{
	(void)str;
	(void)env;
	(void)last_status;
	return (NULL);
}