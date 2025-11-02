#include <stdio.h>

typedef struct messsage_s
{
  char message[140];
  char name[40];
  int msg_len;
} message_t;

int secret_backdoor()
{
  char s[128];

  fgets(s, 128, stdin);
  return system(s);
}

int handle_msg()
{
  message_t msg;
  memset(msg.name, 0, 40); // name is set to 0 as 5 long int(8 bytes)
  msg.msg_len = 140;

  set_username(&msg);
  set_msg(&msg);
  return puts(">: Msg sent!");
}

char *set_msg(message_t *p_msg)
{
  char buffer[1024];

  memset(buffer, 0, sizeof(buffer));
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(buffer, 1024, stdin);
  return strncpy(p_msg->message, buffer, p_msg->msg_len);
}

int set_username(message_t *p_msg)
{
  char buffer[140];
  int i;

  memset(buffer, 0, 128);
  puts(">: Enter your username");
  printf(">>: ");
  fgets(buffer, 128, stdin);
  for (i = 0; i <= 40 && buffer[i]; ++i)
    p_msg->name[i] = buffer[i];
  return printf(">: Welcome, %s", p_msg->name);
}

int main(int argc, const char **argv, const char **envp)
{
  puts(
      "--------------------------------------------\n"
      "|   ~Welcome to l33t-m$n ~    v1337        |\n"
      "--------------------------------------------");
  handle_msg();
  return (0);
}