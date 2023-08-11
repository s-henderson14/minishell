#include "../include/minishell.h"

t_command	*parser(t_tool *shell)
{
    t_token		**tkn_list;
    t_command	*cmd;

	tkn_list = tokeniser(shell->input, shell);
	if (shell->number_of_pipes == 0)
		cmd = create_simple_cmd(tkn_list, shell); //NOTE: create_cmds() may take an extra parameter of t_tool *shell. Not yet decided
	// else if (shell->number_of_pipes > 0)
	// 	cmd = create_cmds(tkn_list, shell);
	return (cmd);
}

int	main() // Tests the use of tokeniser, create_cmds.count_tokens, convert_token_id and beginning of parser
{
	t_command	*cmd;
	int			i;
	t_tool		*shell;
	char		*str;

	str = "ls -la > out";
	shell = ft_calloc(1, sizeof(shell));
	shell->input = ft_calloc(ft_strlen(str), sizeof(char));
	shell->input = str;
	i = 0;
	cmd = parser(shell);
	while (cmd->args[i])
	{
		printf("Arg [%d]: %s\n", i, cmd->args[i]);
		if(cmd->args[i][0] == '>' && cmd->redirection->type == 3)
			printf("|output file|\n");
		else if (cmd->args[i][0] == '<' && cmd->redirection->type == 5)
			printf("<---- input file\n");
		i++;
	}
	return (0);
}