#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2], dump;
	pid_t childpid;
	childpid = fork();
	if (childpid == 0) execlp("unzip", "unzip", "campur2.zip", NULL);
	childpid = fork();
	if (childpid == 0) execlp("touch", "touch", "daftar.txt", NULL);
	while(wait(&dump)>0);
	pipe(fd);
	childpid = fork();
	if (childpid == 0) 
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execlp("ls", "ls", "campur2", NULL);
	}
	char buffer[1024];
	close(fd[1]);
	FILE* rf = fdopen(fd[0], "r");
	FILE *daftar = fopen("daftar.txt", "w");
	int i=0;
	while (fgets(buffer, sizeof(buffer), rf) != NULL) {
		if (strstr(&buffer[strlen(buffer)-5], ".txt") != NULL)
			fprintf(daftar, "%s", buffer);
	}
	fclose(daftar);
}