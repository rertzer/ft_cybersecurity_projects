#include <stdio.h>
#include <stdbool.h>

void clear_stdin(void)
{
  char c = 0;

  while (c != '\n' && c != 255)
  {
    c = getchar();
  }
  return;
}

unsigned int get_unum(void)
{
  unsigned int unsigned_number;

  unsigned_number = 0;
  fflush(stdout);
  scanf("%u", unsigned_number);
  clear_stdin();
  return unsigned_number;
}

int store_number(char *storage)
{
  unsigned int number;
  unsigned int index;
  int error;

  printf(" Number: ");
  number = get_unum();
  printf(" Index: ");
  index = get_unum();
  if ((index % 3 == 0) || (number >> 24 == 183))
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    error = 1;
  }
  else
  {
    *(unsigned int *)(index * 4 + storage) = number;
    error = 0;
  }
  return error;
}

int read_number(char *storage)
{
  unsigned int index;

  printf(" Index: ");
  index = get_unum();
  printf(" Number at data[%u] is %u\n", index, *(unsigned int *)(storage + index * 4));
  return 0;
}

// CONTINUE HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int main(int argc, char **argv, char **envp)
{
  char command[20] = {0};
  int status = 0;
  char storage[100];

  memset(command, 0, 100);

  for (; *argv != '\0'; ++argv)
  {
    memset(*argv, 0, strlen(argv));
  }
  for (; *envp != '\0'; ++envp)
  {
    memset(*envp, 0, strlen(envp));
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
  while (true)
  {
    printf("Input command: ");
    status = 1;
    fgets(command, 20, stdin);

    if (strncmp(command, "store", 5) == 0)
    {
      status = store_number(storage);
    }
    else if (strncmp(command, "read", 4) == 0)
    {
      status = read_number(storage);
    }
    else if (strncmp(command, "quit", 4) == 0)
    {
      return 0;
    }

    if (status == 0)
    {
      printf(" Completed %s command successfully\n", command);
    }
    else
    {
      printf(" Failed to do %s command\n", command);
    }
    /*
    ** it's probably not a memset in the real code;
    ** the assembly do as if it is 5 int set to 0;
    */
    memset(command, 0, 20);
  };
}
