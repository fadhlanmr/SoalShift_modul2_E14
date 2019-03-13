#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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
    DIR *dir;
    struct dirent *file;
    dir = opendir("/home/somi/modul2/soal1/");
    if (dir != NULL){
       while (file = readdir(dir)){
          if (strstr(&file->d_name[strlen(file->d_name)-5], ".png")) {
            char current[256] = "/home/somi/modul2/soal1/",
                 target[256] = "/home/somi/modul2/gambar/",
                 filename[256];
            strncpy(filename, file->d_name, strlen(file->d_name)-4);
            strcat(filename, "_grey.png");
            rename(strcat(current, file->d_name), strcat(target, filename));
          }
        }
    }
    closedir(dir);
    sleep(10);
  }
  
  exit(EXIT_SUCCESS);
}