#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/stat.h"


void xargs(char* argv[]) {
    int pid, status;
    pid = fork();
    if(pid == 0) {
       exec(argv[0], argv);
       exit(0);
    }
    wait(&status);
    return;
}

void main(int argc, char* argv[]) 
{ 
  if(argc - 1 > MAXARG) {
     printf("%s\n", "Parameters are too long");
     exit(1);
  }
  else if(argc < 2) {
     printf("%s\n", "Please enter the appropriate parameters");
     exit(1);
  }

  int i, j;
  char c, buf[512], *xargv[MAXARG];
	
  memset(buf, 0, sizeof(buf));
  for(i = 1; i < argc; i++) {
    xargv[i - 1] = argv[i]; 
  }     
  for(; i < MAXARG; i++) {
    xargv[i] = 0;
  }

  j = 0;
  while(read(0, &c, 1) > 0) {
    if(c != '\n') {
       buf[j++] = c;
    }
    else {
       if(j != 0) {
	 buf[j] = '\0';
	 xargv[argc - 1] = buf;
	 xargs(xargv);
 	 j = 0;  
       } 
    }
  } 

  if(j != 0) {
     buf[j] = '\0';
     xargv[argc - 1] = buf;
     xargs(xargv);
  }
  exit(0); 
}
