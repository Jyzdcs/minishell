/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:57 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../lexer/lexer.h"
# include <stdlib.h>
# include <unistd.h>

/*
** =============================================================================
** FONCTIONS PRINCIPALES D'EXPANSION
** =============================================================================
*/

/**
 * @brief Point d'entrée principal de l'expander
 * @param tokens Liste chaînée de tokens à expander
 * @param env Tableau d'environnement
 * @param last_status Code de retour de la dernière commande
 * @return int 0 si succès, -1 si erreur
 */
int		expand_tokens(t_token *tokens, char **env, int last_status);

/**
 * @brief Expanse les variables d'un token unique
 * @param token Token à traiter
 * @param env Tableau d'environnement
 * @param last_status Code de retour de la dernière commande
 * @return int 0 si succès, -1 si erreur
 */
int		expand_token(t_token *token, char **env, int last_status);

/*
** =============================================================================
** GESTION DES VARIABLES D'ENVIRONNEMENT
** =============================================================================
*/

/**
 * @brief Recherche une variable dans l'environnement
 * @param var_name Nom de la variable à chercher
 * @param env Tableau d'environnement
 * @return char* Valeur de la variable, NULL si inexistante
 */
char	*get_env_value(char *var_name, char **env);

/**
 * @brief Remplace $VAR par sa valeur dans une chaîne
 * @param str Chaîne à traiter
 * @param env Tableau d'environnement
 * @param last_status Code de retour pour $?
 * @return char* Nouvelle chaîne avec substitutions, NULL si erreur
 */
char	*substitute_vars(char *str, char **env, int last_status);

/*
** =============================================================================
** ANALYSE ET EXTRACTION DES VARIABLES
** =============================================================================
*/

/**
 * @brief Extrait le nom d'une variable depuis $VAR
 * @param str Chaîne contenant $VAR
 * @param start Index du caractère $
 * @return char* Nom de la variable, NULL si erreur
 */
char	*extract_var_name(char *str, int start);

/**
 * @brief Trouve la prochaine occurrence de $ dans une chaîne
 * @param str Chaîne à analyser
 * @param start Position de début de recherche
 * @return int Index du $, -1 si non trouvé
 */
int		find_next_dollar(char *str, int start);

/**
 * @brief Vérifie si $ est dans une zone d'expansion autorisée
 * @param str Chaîne complète
 * @param pos Position du $ à vérifier
 * @return bool true si expansion autorisée, false sinon
 */
bool	is_expandable_context(char *str, int pos);

/*
** =============================================================================
** GESTION DES QUOTES POUR L'EXPANSION
** =============================================================================
*/

/**
 * @brief Détermine le type de quote à une position
 * @param str Chaîne à analyser
 * @param pos Position à vérifier
 * @return char Type de quote ('\'', '"', ou 0 si aucune)
 */
char	get_quote_type(char *str, int pos);

/**
 * @brief Trouve la quote fermante correspondante
 * @param str Chaîne à analyser
 * @param start Position de la quote ouvrante
 * @param quote_type Type de quote à chercher
 * @return int Position de la quote fermante, -1 si non trouvée
 */
int		find_closing_quote(char *str, int start, char quote_type);

#endif
