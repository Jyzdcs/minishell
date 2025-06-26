/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <boualemguerroumi21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/25 17:02:28 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_tree *tree)
{
	if (tree->left)
		print_tree(tree->left);
	if (tree->right)
		print_tree(tree->right);
	printf("%s\n", tree->content);
}

int	main(void)
{
	char	*prompt;
	char	**cmnd;
	t_tree	*expr;

	printf ("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	while (1)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
			return (1);
		add_history(prompt);
		if (ft_strncmp(prompt, "", ft_strlen(prompt)) > 0 && !only_spaces(prompt))
		{
			expr = build_tree(ft_split(prompt, ' '), 0, ft_countwords(prompt, ' ') - 1, 2);
			if (!expr)
				return (free(prompt), 2);
			print_tree(expr);
			free_tree(expr);
		}
		free(prompt);
	}
	return (0);
}
