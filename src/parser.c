#include "../include/minishell.h"

t_command	*parser(char *shell) //NOTE: The correct parameter for parser() is t_tool *shell. The use of char * was only for the purposes of testing.
{
    t_token		**tkn_list;
    t_command	*cmd;
	int			i;

	tkn_list = tokeniser(shell);
	cmd = create_cmds(tkn_list); //NOTE: create_cmds() may take an extra parameter of t_tool *shell. Not yet decided
	i = 0;
	while (i < count_tokens(tkn_list))
	{
		printf("Arg no.%d is %s\n", i,cmd->args[i]);
		i++;
	}
	return (cmd);
}

int	main(int argc, char **argv) // Tests the use of tokeniser, create_cmds.count_tokens, convert_token_id and beginning of parser
{
	(void)argc;

	parser(argv[1]);
	return (0);
}