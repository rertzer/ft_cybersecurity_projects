#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int auth(char *login, int serial)
{
    int i;
    int computed;
    int login_len;

    login[strcspn(login, "\n")] = 0;
    login_len = strnlen(login, 32);
    if (login_len <= 5)
        return 1;
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
    {
        puts("\x1B[32m.---------------------------.");
        puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1B[32m'---------------------------'");
        return 1;
    }
    else
    {
        computed = (login[3] ^ 0x1337) + 6221293; // 0x1335 = 4919
        for (i = 0; i < login_len; ++i)
        {
            if (login[i] <= 31)
                return 1;
            computed += (computed ^ (unsigned int)login[i]) % 0x539; // 0x539 = 1337
        }
        return serial != computed;
    }
}

int main(int argc, const char **argv, const char **envp)
{
    int serial;
    char login[28];

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);
    if (auth(login, serial))
        return 1;
    puts("Authenticated!");
    system("/bin/sh");
    return 0;
}
