#include "../../include/minishell.h"

/*
SIG_DFL
SIG_DFL specifies the default action for the particular signal. The default actions for various kinds of signals are stated in Standard Signals.

SIG_IGN
SIG_IGN specifies that the signal should be ignored.
*/

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_sig = 130;
	 	rl_on_new_line();
	 //	rl_replace_line("", 0);
	 	rl_redisplay();
	}
	else
		g_sig = 131;
}

void signal_parent()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void signal_init()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void signal_child()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_DFL);
}

void signal_noninteractive()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
//interactivemod

//non interactive -- heredoc related, while reading a script


// int init_signal(void)
// {
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal_flag = 2;
// 	}
// 	else if (sigaction(SIGTERM, &sa, NULL) == -1)
// 	{
// 		(SIGTERM);
// 		signal_flag = 1;
// 	}
// 	return (signal_flag);
// }
//this returns global flag for the case "signal received??"
//if necessary it exits the prgoram, or get the prompt back??

