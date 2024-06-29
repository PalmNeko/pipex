#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd;
    int index;
    int fds[2];
    char buf[300];

    sleep(3000);
    return (0);
    pipe(fds);
    index = 0;
    int pre_fds[2] = {dup(fds[0]), dup(fds[1])};
    int now_fds[2];
    while (index < 10)
    {
        int cpid;

        pipe(now_fds);
        cpid = fork();
        if (cpid == 0)
        {
            dup2(now_fds[1], 1);
            dup2(pre_fds[0], 0);
            close(fds[1]);
            close(fds[0]);
            close(now_fds[1]);
            close(now_fds[0]);
            close(pre_fds[1]);
            close(pre_fds[0]);
            write(1, buf, read(0, buf, 300));
            return (0);
        }
        close(pre_fds[0]);
        close(pre_fds[1]);
        pre_fds[0] = now_fds[0];
        pre_fds[1] = now_fds[1];
        index++;
    }
    write(fds[1], buf, read(0, buf, 300));
    write(1, buf, read(pre_fds[0], buf, 300));
    wait(NULL);
    close(pre_fds[1]);
    close(pre_fds[0]);
    close(fds[0]);
    close(fds[1]);
    sleep(3000);
    return (0);
}