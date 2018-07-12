#include "minishell.h"

static void		sig_int(int sig)
{
	(void)sig;
	tcsetattr(0, 0, &g_mini.copy_term);
//	printf("\nsignal catched !\n");
	exit(1);
}

static void		sig_tstp(int sig)
{
	(void)sig;
	tcsetattr(0, TCSANOW, &g_mini.copy_term);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

static void		sig_cont(int sig)
{
	(void)sig;
	signal(SIGTSTP, &sig_tstp);
	init(&g_mini.copy_term);
}

void	sigtest(void)
{
	int i;

	i = 1;
	while (i < 16)
	{
		signal(i, sig_int);
		i++;
	}
	signal(SIGTSTP, sig_tstp);
	signal(SIGCONT, sig_cont);
}

int			init(struct termios *copy_term)
{
	char			*name_term;
	struct termios	term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Hey, bring back env bro\n", 2);
		return (-1);
	}
/*	if (tgetent(NULL, name_term) == -1)
		return (-1);
*/	if (tcgetattr(0, &term) == -1)
		return (-1);
	*copy_term = term;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}
