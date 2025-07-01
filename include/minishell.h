/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:02:20 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/25 11:08:31 by bguerrou         ###   ########.fr       */
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

t_tree	*build_tree(char **expr, int left, int right, int prio);
void	free_tree(t_tree *tree);

#endif