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

  struct stat st = {0};
  if (stat("/home/somi/log", &st) == -1) {
      mkdir("/home/somi/log", 0777);
  }
  int i=0;
  char folder[150] = "";
  while(1) {
    if (!i) {
      memset(&folder[0], 0, sizeof(folder));
      strcpy(folder, "/home/somi/log/");
      time_t rawtime;
      struct tm * timeinfo;
      char buffer [80];
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      strftime(buffer, sizeof(buffer), "%d:%m:%Y-%R", timeinfo);
      struct stat st2 = {0};
      if (stat(strcat(folder,buffer), &st2) == -1) {
          mkdir(folder, 0777);
      }
    }
    char log[150] = "";
    strcat(log, folder);
    char temp[20] = "";
    sprintf(temp, "/log%d.log", i+1);
    strcat(log, temp);
    FILE *syslog = fopen("/var/log/syslog", "r");
    FILE *filelog = fopen(log, "w");
    char ch;
    while ((ch = fgetc(syslog)) != EOF)
          fputc(ch, filelog);
        fclose(syslog);
        fclose(filelog);
    if (++i == 30) i=0;
    sleep(60);
  }
  
  exit(EXIT_SUCCESS);
}
