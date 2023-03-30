#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int 
main(int argc, char* argv[]) 
{
  if(argc < 2) {
    printf("Error: no parameters were given.\n");
    exit(0);
  }
  
  int sleep_sec;
  
  sleep_sec = atoi(argv[1]);
  if(sleep_sec >= 0) {
    sleep(sleep_sec);
  }
  else{
    printf("Invalid interval %s.\n", argv[1]);
  }  
  
  exit(0);  
}
