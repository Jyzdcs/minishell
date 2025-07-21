/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/21 21:00:14 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*prompt;
	t_token	*tokens;
	t_token	*current;

	// printf("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	while (1)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
		{
			printf("exit\n");
			break ;
		}
		tokens = lexer(prompt);
		if (tokens == NULL)
		{
			printf("❌ Erreur: quotes non fermées ou input vide\n");
		}
		else
		{
			current = tokens;
			while (current)
			{
				printf("Token: '%s' (type: %d)\n", current->value,
					current->type);
				current = current->next;
			}
			free_tokens(tokens);
		}
		add_history(prompt);
		free(prompt);
	}
	return (0);
}
