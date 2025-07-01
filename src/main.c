/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/06/30 19:25:53 by bguerrou         ###   ########.fr       */
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
	t_tree	*expr;
	t_line	*ligne;

	printf("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	ligne = malloc(sizeof(t_line));
	if (!ligne)
		return (-1);
	while (1)
	{
		ligne->prompt = readline("minishishishi > ");
		if (!ligne->prompt)
			return (1);
		add_history(ligne->prompt);
		if (ft_strncmp(ligne->prompt, "", ft_strlen(ligne->prompt)) > 0 && !only_spaces(ligne->prompt))
		{
			ligne->cmnd = parse_prompt(ligne->prompt, ligne);
			if (!ligne->cmnd)
				return (free(ligne->prompt), 2);
			expr = build_tree(ft_split(ligne->prompt, ' '), 0, ft_countwords(ligne->prompt, ' ') - 1, 2);
			if (!expr)
				return (free(ligne->prompt), free_arr(ligne->cmnd, ligne->cmnd_size), 3);
			free_tree(expr);
		}
		free(ligne->prompt);
		free_arr(ligne->cmnd, ligne->cmnd_size);
	}
	return (0);
}
