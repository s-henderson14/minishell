#include "../../include/minishell.h"

void	add_cmd_front(t_command **cmd_lst, t_command *new_cmd)
{
	new_cmd->next = *cmd_lst;
	*cmd_lst = new_cmd;
}

void	add_cmd_back(t_command **cmd_lst, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *cmd_lst;
	if (*cmd_lst == NULL)
	{	
		add_cmd_front(cmd_lst, new_cmd);
		return ;
	}
  	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

int	word_counter(const char *s, char c)
{
	int	count;
	int	i;

	i = 0; ////Example of "ls -l | grep libft" become "ls -l" "grep libft"
	count = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '|' || s[i] != '>' || s[i] != '<') //changed to remove pipes and redirections from command args
		{	
			while (s[i] && s[i] != c)
			{	
				i++;
				if (s[i] == c || s[i] == '\0')
					count++;
			}
		}
		else
			i++;// added as part of removing pipes and redirections from command args
	}
	return (count);
}


// int	word_counter(const char *s, char c)
// {
// 	int	count;
// 	int	i;
// 	char prev_char;

// 	i = 0;
// 	count = 0;
// 	prev_char = '\0';

// 	if (s == NULL)
// 		return (0);
// 	while (s[i] != '\0')
// 	{

// 		if (s[i] == c && prev_char != c) // to handle consecutive " "
// 		{
// 			count++;
// 		}
// 		if (i > 0) 
// 		{
// 			prev_char = s[i]; // to keep prev_char behind s[i]
// 		}
// 		i++;
// 	}
// 	return (count);
// }