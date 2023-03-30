#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) 
{
  int father_fd[2];
  int child_fd[2]; 
  int PID;
  char buff[64];
  
  pipe(father_fd);
  pipe(child_fd);
  
  
  PID = fork();
  
  if(PID > 0) {
    close(father_fd[0]);
    write(father_fd[1],"ping", 4);
    close(child_fd[1]);
    read(child_fd[0], buff, 4);
    printf("%d: received %s\n", getpid(), buff);
  }
  else if(PID == 0) {
    close(father_fd[1]);
    read(father_fd[0], buff, 4);
    close(child_fd[0]);
    printf("%d: received %s\n", getpid(), buff);
    write(child_fd[1], "pong", 4); 
  }

  exit(0); 
}
