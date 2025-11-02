#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool auth(char *login, int serial)
{
    int i;         // [esp+14h] [ebp-14h]
    int computed;  // [esp+18h] [ebp-10h]
    int login_len; // [esp+1Ch] [ebp-Ch]

    login[strcspn(login, "\n")] = 0;
    login_len = strnlen(login, 32);
    printf("login length is  %d\n", login_len);
    if (login_len <= 5)
        return 1;
    
        computed = (login[3] ^ 0x1337) + 6221293; // 0x1335 = 4919
        for (i = 0; i < login_len; ++i)
        {
            if (login[i] <= 31)
                return 1;
            computed += (computed ^ (unsigned int)login[i]) % 0x539; // 0x539 = 1337
        }
        printf("%s %d %d\n", login, serial, computed);
        return serial != computed;

}

int main(int argc, const char **argv, const char **envp)
{
    int serial;      // [esp+2Ch] [ebp-24h] BYREF
    char login[32];  // [esp+30h] [ebp-20h] BYREF



    puts("***********************************");
    puts("*\t\t auth \t\t  *");
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
    return 0;
}