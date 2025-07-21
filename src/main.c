/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:55:47 by bguerrou          #+#    #+#             */
/*   Updated: 2025/07/21 16:51:48 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*prompt;
	t_token	*tokens;

	printf("\033[37;2m\n%s\n\033[0m\n", LUFFY);
	while (1)
	{
		prompt = readline("minishishishi > ");
		if (!prompt)
		{
			printf("exit\n");
			break ;
		}
		// Commande exit explicite
		if (ft_strncmp(prompt, "exit", 4) == 0)
		{
			free(prompt);
			break ;
		}
		tokens = lexer(prompt);
		if (tokens == NULL)
		{
			printf("\n");
		}
		free_tokens(tokens);
		add_history(prompt);
		free(prompt);
	}
	return (0);
}
