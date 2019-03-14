#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    const char *makan = "/home/somi/Documents/makanan/makan_enak.txt";
    struct stat info;
    stat(makan, &info); 
    // printf("%ld\n", info.st_atime);
    // printf("%ld\n", time(NULL));
    if (info.st_atime > time(NULL)-30) {
      int i=1;
      while (1) {
        char dir[200] = "/home/somi/Documents/makanan/makan_sehat";
        char str[20] = "";
        sprintf(str, "%d", i);
        strcat(str, ".txt");
        strcat(dir, str);
        FILE *sehat = fopen(dir, "r");
        if (!sehat) {
          FILE *baru = fopen(dir, "w");
          fclose(baru);
          break;
        }
        fclose(sehat);
        i++;
      }
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
