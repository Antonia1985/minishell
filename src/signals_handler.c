#include "minishell.h"
#include "libft.h"

void    my_handler(int signal)
{
    (void)signal;	
	if (g_exit_status == 130)
		return; // do nothing — heredoc handler already handled it
    rl_replace_line("", 0); //Replaces Readline’s editing buffer (the text the user has been typing) with the given text
    rl_on_new_line();       //Internally it resets Readline’s idea of the current cursor position to the start of a line.
    write(1, "\n", 1);      //Forces Readline to redraw the prompt and the contents of its editing buffer on the current line
	//write(1, "in my_handler orig", 18);
    rl_redisplay();
}

void    signals_handler()
{
    //Ctrl-\ -- SIGQUIT (“quit”) --> SIG_IGN //  Ctrl-\ tells the terminal to send SIGQUIT (“quit”).
	struct sigaction sa1;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	sa1.sa_handler = SIG_IGN;
	if(sigaction(SIGQUIT, &sa1, NULL) == -1) 
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	//Ctrl-C -- SIGINT (interupt) --> print \n and give the prompt back
	struct sigaction sa2;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_RESTART;
	sa2.sa_handler = my_handler;
    if(sigaction(SIGINT, &sa2, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/*
	A signal mask is simply a set of signals that are currently blocked 
	from being delivered to your thread. 
	When a signal is blocked, it won’t be delivered immediately, 
	instead it becomes “pending” until you unblock it. Here’s what you need to know:
	--	sa_mask in struct sigaction:
		When you install a handler, you can specify 
		an additional mask of signals to block while your handler is running.
		That ensures e.g. your SIGINT handler can block SIGQUIT (or itself) until it returns
*/
