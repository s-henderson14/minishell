#include "../include/minishell.h"

int	meta_found(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 34)
			count++;
		i++;
	}
	if (count > 0 && count % 2 != 0)
		exit(EXIT_FAILURE);
	else if (count > 0 && count % 2 == 0)
		return(1);
	else
		return (0);	

}

int dollar_sign_found(char *string)
{
	int	i;

	i = 1;
	while (string[i])
	{	
		if (string[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strsame(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}


int check_key_exists(char *key, t_env_node *env_list)
{
	while (env_list != NULL)
	{
		if (ft_strsame(ft_strchr(key, '$') + 1, env_list->key) == 1)
			return (1);
		env_list = env_list->next;
	}
	return (0);
}
char	*get_value_from_env_node(char *key, t_env_node *env_list)
{
	char *value;
	if (check_key_exists(key, env_list) == 0)
		return (NULL);
	while (env_list != NULL)
	{
		if (ft_strsame(ft_strchr(key, '$') + 1, env_list->key) == 1)
		{
			value = ft_strdup(env_list->value);
			return (value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
