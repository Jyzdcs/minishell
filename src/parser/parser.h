/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:51:04 by kclaudan          #+#    #+#             */
/*   Updated: 2025/07/02 23:15:22 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H
# include "../lexer/lexer.h"	

// Structure de liste chainee pour les commandes
typedef struct s_cmd
{
	char			**argv;			// Tableau d'arguments (NULL-terminated)
	int				argc;			// Nombre d'arguments
	int				infile;			// FD d'entrée (-1 si stdin)
	int				outfile;		// FD de sortie (-1 si stdout)
	bool			append_mode;	// Mode append pour >>
	char			*heredoc_delim;	// Délimiteur pour heredoc
	struct s_cmd	*next;			// Commande suivante (pipe)
}					t_cmd;

// =============================================================================
// FONCTIONS DE PARSING PRINCIPAL
// =============================================================================

/**
 * @brief Point d'entrée principal du parser
 * @param tokens Liste chaînée de tokens à parser
 * @return t_cmd* Liste chaînée de commandes parsées, NULL si erreur
 */
t_cmd	*parse_tokens(t_token *tokens);

/**
 * @brief Crée une nouvelle structure de commande initialisée
 * @return t_cmd* Nouvelle commande initialisée, NULL si erreur
 */
t_cmd	*create_cmd(void);

/**
 * @brief Ajoute une commande à la fin de la liste
 * @param list Pointeur vers la tête de liste
 * @param cmd Commande à ajouter
 */
void	add_cmd(t_cmd **list, t_cmd *cmd);

// =============================================================================
// CONSTRUCTION DES COMMANDES
// =============================================================================

/**
 * @brief Construit le tableau argv à partir des tokens
 * @param tokens Liste de tokens pour une commande
 * @return char** Tableau d'arguments, NULL si erreur
 */
char	**build_argv(t_token *tokens);

/**
 * @brief Compte le nombre d'arguments dans une séquence de tokens
 * @param tokens Liste de tokens à analyser
 * @return int Nombre d'arguments
 */
int		count_args(t_token *tokens);

/**
 * @brief Remplit le tableau argv avec les valeurs des tokens
 * @param argv Tableau à remplir
 * @param tokens Liste de tokens source
 */
void	fill_argv(char **argv, t_token *tokens);

// =============================================================================
// GESTION DES REDIRECTIONS
// =============================================================================

/**
 * @brief Traite une redirection et met à jour la commande
 * @param cmd Commande à modifier
 * @param token Token de redirection
 * @return int 0 si succès, -1 si erreur
 */
int		handle_redirection(t_cmd *cmd, t_token *token);

/**
 * @brief Ouvre un fichier d'entrée
 * @param filename Nom du fichier à ouvrir
 * @return int File descriptor, -1 si erreur
 */
int		open_input_file(char *filename);

/**
 * @brief Ouvre un fichier de sortie
 * @param filename Nom du fichier à ouvrir
 * @param append true pour mode append (>>), false pour écrasement (>)
 * @return int File descriptor, -1 si erreur
 */
int		open_output_file(char *filename, bool append);

/**
 * @brief Gère un heredoc (<<)
 * @param delimiter Délimiteur de fin
 * @return int File descriptor du heredoc, -1 si erreur
 */
int		handle_heredoc(char *delimiter);

// =============================================================================
// VALIDATION SYNTAXIQUE
// =============================================================================

/**
 * @brief Valide la syntaxe globale des tokens
 * @param tokens Liste de tokens à valider
 * @return bool true si syntaxe valide, false sinon
 */
bool	is_valid_syntax(t_token *tokens);

/**
 * @brief Vérifie la cohérence des redirections
 * @param tokens Liste de tokens à vérifier
 * @return bool true si redirections valides, false sinon
 */
bool	check_redirections(t_token *tokens);

/**
 * @brief Vérifie la cohérence des pipes
 * @param tokens Liste de tokens à vérifier
 * @return bool true si pipes valides, false sinon
 */
bool	check_pipes(t_token *tokens);

#endif