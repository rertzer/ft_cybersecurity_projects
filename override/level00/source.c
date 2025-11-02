#include <stdio.h>

int main(void)
{
  int result;
  int password;

  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &password);
  if (password == 5276)
  {
    puts("\nAuthenticated!");
    system("/bin/sh");
    result = 0;
  }
  else
  {
    puts("\nInvalid Password!");
    result = 1;
  }
  return (result);
}