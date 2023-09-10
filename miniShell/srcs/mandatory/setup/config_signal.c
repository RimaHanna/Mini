#include "minishell.h"

extern long long	g_last_exit_status;

/**
 * This function is a signal handler for the SIGINT signal.
 * SIGINT is generated when the user presses Ctrl+C to interrupt a running 
 * program.
 * When SIGINT is received, it performs the following actions:
 *
 * 1. Prints a newline character to standard output to ensure the prompt starts 
 * on a new line.
 * 2. Sets the g_last_exit_status variable to 130, indicating the interruption.
 * 3. Exits the program with an exit status of 130.
 *
 * @param signum - The signal number, expected to be SIGINT.
 */
void child_signals(int signum)
{
    if (signum == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        g_last_exit_status = 130;
        exit(130);
    }
}

/**
 * This function is another signal handler for the SIGINT signal.
 * When SIGINT is received, it performs the following actions:
 *
 * 1. Prints a newline character to standard output.
 * 2. Utilizes functions from the readline library to manage command line input.
 *    It clears the current line, displays a new prompt, and effectively cancels 
 *    the current input line.
 * 3. Sets the g_last_exit_status variable to 130.
 *
 * @param signum - The signal number, expected to be SIGINT.
 */
void dismiss_signal(int signum)
{
    if (signum == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_last_exit_status = 130;
    }
}

/**
 * This function configures signal handling for the shell program.
 * It uses the sigaction system call to set up a custom signal handler for 
 * SIGINT (interrupt signal).
 * The SIGINT handler is set to dismiss_signal, which clears the input line and 
 * sets the g_last_exit_status variable.
 * The SA_RESTART flag is set to allow system calls interrupted by a signal to 
 * restart automatically.
 * The signal mask (sa.sa_mask) is set to block SIGINT while the signal handler 
 * is running.
 * Additionally, it uses the signal function to ignore the SIGQUIT signal,
 * typically generated when the user presses Ctrl+\ to quit a program.
 */
void config_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &dismiss_signal;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
