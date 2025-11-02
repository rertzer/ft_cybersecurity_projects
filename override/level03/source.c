#include <stdio.h>

int decrypt(int password)
{
  int status;
  unsigned int i;
  unsigned int length;
  char secret[29];

  secret[17] = 0;
  strcpy(secret, "Q}|u`sfg~sf{}|a3");
  length = strlen(secret);
  for (i = 0; i < length; ++i)
    secret[i] ^= password;
  if (strcmp(secret, "Congratulations!") == 0)
    status = system("/bin/sh");
  else
    status = puts("\nInvalid Password");
  return (status);
}

int test(int password, int baseline)
{
  int result;
  int random;

  switch (baseline - password)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
    result = decrypt(baseline - password);
    break;
  default:
    random = rand();
    result = decrypt(random);
    break;
  }
  return (result);
}

int main(void)
{
  unsigned int seed;
  int password;

  seed = time(0);
  srand(seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &password);
  test(password, 322424845);
  return (0);
}