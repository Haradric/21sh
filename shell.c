/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:54 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/14 14:45:56 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**g_env;

int		shell_interactive(void)
{
	t_list	*tokens;
	t_list	*hist;
	char	*input;
	int		exit;

	tokens = NULL;
	hist = NULL;
	exit = 0;
	while (!exit)
	{
		if (!(input = get_input(get_env_var("PROMPT"), &hist)))
			continue ;
		if (!ft_strcmp(input, "exit"))
			break ;
		tokens = get_token_list(input);
		run_command(tokens);
		ft_lstfreelist(&tokens, free_token);
	}
	ft_lstfreelist(&hist, free);
	return (exit);
}

int		shell_noninteractive(int argc, char **argv)
{
	if (argc > 1 && !ft_strcmp(argv[1], "--test"))
		terminate("21sh:", "there is no tests");
	else
		terminate("21sh: ", "sorry, non-interactive mode is not supported yet");
	return (0);
}
