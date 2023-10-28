#include "../../include/minishell.h"

// struct sigaction {
//     void   (*sa_handler)(int);    /* Address of handler */
//     sigset_t sa_mask;             /* Signals blocked during handler
//                                      invocation */
//     int      sa_flags;            /* Flags controlling handler invocation */
//     void   (*sa_restorer)(void);  /* Not for application use */
// };

// struct sigaction sa;
int signal_flag = 0;

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		signal_flag = SIGINT;
		rl_on_new_line();
		rl_redisplay();

	}
	else
	{
		signal_flag = SIGTERM;
	}
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

