#include <unistd.h>
#include <stdio.h>

void check(const char *filename, int mode, const char *message)
{
    if (access(filename, mode) == 0)
        printf("%s OK!\n", message);
    else
        perror(message);
}
int main(int argc, char *argv[])
{
    if (argc != 2)
        return (0);
    if (setuid(1000) != 0)
        perror("setuid");
    uid_t uid = getuid();
    printf("uid: %d\n", getuid());
    check(argv[1], F_OK, "exists");
    check(argv[1], R_OK, "read");
    check(argv[1], W_OK, "write");
    check(argv[1], X_OK, "execute");
    char c;
    read(0, &c, 1);
    return (0);
}
