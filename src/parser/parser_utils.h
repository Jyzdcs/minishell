/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:39 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H
# include "parser.h"

/**
 * @brief Initialise proprement une structure t_cmd
 * @param cmd Structure à initialiser
 */
void	init_cmd(t_cmd *cmd);

/**
 * @brief Ferme un fd seulement s'il est valide (> 2)
 * @param fd File descriptor à fermer
 */
void	safe_close(int fd);

/**
 * @brief Compte les arguments CMD/ARG jusqu'au prochain pipe
 * @param tokens Début du segment
 * @return int Nombre d'arguments pour argv
 */
int		count_cmd_args(t_token *tokens);

/**
 * @brief Vérifie si un token est une redirection
 * @param type Type de token à tester
 * @return bool true si redirection, false sinon
 */
bool	is_redirection(t_token_type type);


/**
 * @brief Libère la mémoire de toute la liste de commandes
 * @param cmds Liste de commandes à libérer
 */
void	free_cmds(t_cmd *cmds);

/**
 * @brief Libère un tableau argv
 * @param argv Tableau à libérer
 */
void	free_argv(char **argv);

/**
 * @brief Navigue jusqu'au prochain token pipe
 * @param tokens Position actuelle dans la liste
 * @return t_token* Token pipe ou NULL si fin de liste
 */
t_token	*skip_to_pipe(t_token *tokens);

#endif 