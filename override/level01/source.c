#include <stdio.h>

char a_user_name[100];

int verify_user_name(void)
{
  puts("verifying username....\n");
  return (memcmp(a_user_name, "dat_wil", 7) != 0);
}

int verify_user_pass(const char *password)
{
  return (strcmp(password, "admin", 5) != 0);
}

int main(void)
{
  char password[64];
  int test;

  memset(password, 0, sizeof(password));
  test = 0;

  puts("********* ADMIN LOGIN PROMPT *********");

  printf("Enter Username: ");
  fgets(a_user_name, 256, stdin);
  test = verify_user_name();

  if (test != 0)
  {
    puts("nope, incorrect username...\n");
  }
  else
  {
    puts("Enter Password: ");
    fgets(password, 100, stdin);
    test = verify_user_pass(password);
    puts("nope, incorrect password...\n");
  }
  return (1);
}