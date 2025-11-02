#include <stdio.h>

unsigned int log_wrapper(FILE *file, const char *log_msg, const char *file_path)
{
  char dest[264];

  strcpy(dest, log_msg);
  snprintf(&dest[strlen(dest)], 254 - strlen(dest), file_path);
  
  dest[strcspn(dest, "\n")] = 0;
  fprintf(file, "LOG: %s\n", dest);
  return 0;
}

int main(int argc, const char **argv)
{
  FILE *file;
  FILE *stream;
  int fd;
  char buf;
  char dest[104];

  buf = 255;

  if ( argc != 2 ) {
    printf("Usage: %s filename\n", *argv);
  }

  file = fopen("./backups/.log", "w");
  if (!file) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }

  log_wrapper(file, "Starting back up: ", argv[1]);

  stream = fopen(argv[1], "r");
  if (!stream) {
    printf("ERROR: Failed to open %s\n", argv[1]);
    exit(1);
  }

  strcpy(dest, "./backups/");
  strncat(dest, argv[1], 99 - strlen(dest));
  
  fd = open(dest, 193, 432);
  if (fd < 0) {
    printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
    exit(1);
  }

  while (1) {
    buf = fgetc(stream);
    if ( buf == (char)255 )
      break;
    write(fd, &buf, 1);
  }

  log_wrapper(file, "Finished back up ", argv[1]);
  
  fclose(stream);
  close(fd);
  return 0;
}
