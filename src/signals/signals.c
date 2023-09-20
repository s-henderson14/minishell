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
		signal_flag = SIGINT;

	}
	else if (signum == SIGTERM)
	{
		signal_flag = SIGTERM;
		kill(0, SIGTERM);
	}
}
//interactivemod

//non interactive -- heredoc related, while reading a script


int init_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        signal_handler(SIGINT);
        signal_flag = 2;
    }
    else if (sigaction(SIGTERM, &sa, NULL) == -1)
    {
        signal_handler(SIGTERM);
        signal_flag = 1;
    }
    return (signal_flag);
}
//this returns global flag for the case "signal received??"
//if necessary it exits the prgoram, or get the prompt back??

