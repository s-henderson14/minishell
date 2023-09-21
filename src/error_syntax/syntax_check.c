#include <stdio.h>

int	unclosed_quotes(char **argv)
{
	int	i;
	int	j;
	int	double_q;
	int	single_q;

	i = 0;
	j = 0;
	double_q = 0;
	single_q = 0;
	while (argv[++i])
	{
		while (argv[i][j])
		{	
			if (argv[i][j] == 39)
				single_q++;
			else if (argv[i][j] == 34)
				double_q++;
			j++;
		}
		printf("%s\n", argv[i]);
	}
	if ((single_q % 2 == 1) || double_q % 2 == 1)
	{	
		perror("Syntax error: unclosed quotations are undefined in this implementation\n");
		return (-1);
	}
	return (0);
}


