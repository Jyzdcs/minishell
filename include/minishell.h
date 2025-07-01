/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:20 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/30 19:25:06 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# include "luffy.h"

// Structure d'arbre binaire pour interpréter les commandes
typedef struct s_tree
{
	char			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_line
{
	char	*prompt;
	char	**cmnd;
	int		cmnd_size;
}			t_line;

// Parser
char 	**parse_prompt(char *prompt, t_line *ligne);

// Lexer
t_tree	*build_tree(char **expr, int left, int right, int prio);

// Expander
char	*expand(char *str);

// Trees
t_tree	*create_branch(char *content);
void	free_tree(t_tree *tree);

// Tools
int		only_spaces(char *str);
int		till_sep(char *str);
char	*var_name(char *str);
void	free_arr(char **arr, int size);
int		arr_size(char **arr);

#endif