#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	kill(pid, SIGTERM);
	return (0);
}
