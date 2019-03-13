
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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
    struct stat file;
    const char *elen = "/home/somi/modul2/soal2/hatiku/elen.ku";
	stat(elen, &file);
	if (access(elen, F_OK) == 0) {
		chmod(elen, S_IRWXU|S_IRWXG|S_IRWXO);
		struct group *grp;
		struct passwd *user;
		grp = getgrgid(file.st_gid);
		user = getpwuid(file.st_uid);
		if (strcmp(user->pw_name, "www-data") == 0 && strcmp(grp->gr_name, "www-data") == 0)
			remove(elen);
	}
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}