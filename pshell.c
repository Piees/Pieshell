#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#define chdir _chdir

#else
#include <unistd.h>
#endif

#define MAX_LENGTH 1024
#define DELIMS " \t\r\n"


int main(int argc, char *argv[]) {
  char *cmd;
  char line[MAX_LENGTH];

//hva vi må ha med:
// parser, starte prossess og må kunne svare

printf("__________.__              .__           .__  .__   \n");
printf("\\______   \\__| ____   _____|  |__   ____ |  | |  |  \n");
printf(" |     ___/  |/ __ \\ /  ___/  |  \\_/ __ \\|  | |  |  \n");
printf(" |    |   |  \\  ___/ \\___ \\|   Y  \\  ___/|  |_|  |__\n");
printf(" |____|   |__|\\___  >____  >___|  /\\___  >____/____/\n");
printf("                  \\/     \\/     \\/     \\/           \n");
printf("Dont believe the fish!\n");

  while (1) {
    printf("$ ");
    if (!fgets(line, MAX_LENGTH, stdin)) break;

    // Parse and execute command
    if ((cmd = strtok(line, DELIMS))) {
      // Clear errors
      errno = 0;

      // Execute chdir through chdir
      if (strcmp(cmd, "cd") == 0) {
        char *arg = strtok(0, DELIMS);

        if (!arg) fprintf(stderr, "cd missing argument.\n");
        else  {
          chdir(arg);
          system("ls");
        }

      // Make file
      } else if (strcmp(cmd, "mkfile") == 0) {
        char *arg = strtok(0, DELIMS);

        if (!arg) fprintf(stderr, "specify file name.\n");
        else {
          FILE *fp = fopen(arg, "ab+");
          fclose(fp);
        }

      // Print to terminal
      } else if (strcmp(cmd, "echo") == 0) {
        char *arg;
        arg = strtok(0, DELIMS);

        if (!arg) fprintf(stderr, "specify a string.\n");
        else {
          while (arg != NULL) {
            if (strcmp(arg, "<") != 0) {
              printf(arg);
              fprintf(stdout, "\n");
              arg = strtok(NULL, DELIMS);
            }
          }
        }

      // Lying fish
      } else if (strcmp(cmd, "fish") == 0) {
        fprintf(stdout, "Gobble gobble, this fish is a lie.\n");

      // Exit shell
      } else if (strcmp(cmd, "exit") == 0) {
        break;

      // Try system command
      } else system(line);

      if (errno) perror("Command failed");
    }
  }

  return 0;
}
