/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:12:07 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/25 16:00:26 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_prio(char *expr)
{
	int	exprlen;

	exprlen = ft_strlen(expr);
	if (ft_strncmp(expr, "|", ft_strlen(expr)) == 0)
		return (2);
	if (!ft_strncmp(expr, ">", exprlen) || !ft_strncmp(expr, "<", exprlen)
		|| !ft_strncmp(expr, "<<", exprlen) || !ft_strncmp(expr, ">>", exprlen))
		return (1);
	else
		return (0);
}

t_tree	*build_tree(char **expr, int left, int right, int prio)
{
	int		i;
	t_tree	*tree;

	if (prio < 0)
		return (NULL);
	i = right;
	while (i >= left && count_prio(expr[i]) != prio)
		i--;
	if (i < left)
		return (build_tree(expr, left, right, prio - 1));
	tree = create_branch(expr[i]);
	if (!tree)
		return (NULL);
	if (prio > 0)
		tree->left = build_tree(expr, left, i - 1, prio);
	if (prio > 0)
			tree->right = build_tree(expr, i + 1, right, prio);
	if (prio > 0 && (!tree->left || !tree->left))
		free_tree(tree);
	return (tree);
}
