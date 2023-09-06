#include "../include/minishell.h"

t_command	**parser(t_tool *shell)
{
    t_token		**tkn_list;
    t_command	**cmd;

	tkn_list = tokeniser(shell->input, shell);
	if (shell->number_of_pipes == 0)
		cmd = create_simple_cmd(tkn_list, shell);
	else if (shell->number_of_pipes > 0)
		cmd = create_adv_cmd(tkn_list, shell);
	return (cmd);
}

int	main() // Tests the use of tokeniser, create_cmds.count_tokens, convert_token_id and beginning of parser
{
	t_command	**cmd;
	t_command	*tmp;
	t_tool		*shell;
	char		*str;
	int			i;

	str = "ls wc -l";
	i = 0;
	shell = ft_calloc(1, sizeof(t_tool));
	shell->input = ft_calloc(ft_strlen(str)  + 1, sizeof(char));
	ft_strlcpy(shell->input, str, ft_strlen(str) + 1);
	cmd = parser(shell);
	tmp = *cmd;
	while (tmp != NULL)
	{
		while (tmp->args[i])
		{
			printf("Arg [%d]: %s\n", i, tmp->args[i]);
			if(tmp->args[i][0] == '>' && tmp->redirection->type == 3)
				printf("|output file|\n");
			else if (tmp->args[i][0] == '<' && tmp->redirection->type == 5)
				printf("<---- input file\n");
			i++;
		}
		tmp = tmp->next;
		if (tmp)
			printf("Second Command");
		i = 0;
	}
	return (0);
}