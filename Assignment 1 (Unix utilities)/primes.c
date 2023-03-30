#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



void helper(int tube) {
   
   int p, q, num, status;
   q = read(tube, &p, sizeof(int));
   if(q == 0) return;

   printf("%s %d\n", "prime", p);

   int another_tube[2];
   pipe(another_tube);
     
   int pid = fork();
   if(pid < 0) {
     printf("fork failure!");
     exit(1);
   }

   if(pid > 0) {
      close(another_tube[0]);
      while(read(tube, &num, sizeof(int)) > 0) {
         if(num % p != 0) write(another_tube[1], &num, sizeof(int));
      }
      close(another_tube[1]);
   }
   else {
      close(another_tube[1]);
      helper(another_tube[0]);
      close(another_tube[0]);
      exit(0);
   }
   wait(&status);
}


void main(int argc, char* argv[]) {

   int tube[2];
   pipe(tube);
   
   int pid = fork();
   int i, status;
   
   if(pid < 0) {
     printf("fork failure!");
     exit(1);
   } 

   if(pid > 0) {
     close(tube[0]);
     for(i = 2; i <= 35; i++) {
        write(tube[1], &i, sizeof(int));
     }
     close(tube[1]);
   }
   else {
     close(tube[1]);     
     helper(tube[0]);
     close(tube[0]);
     exit(0);
   }

   wait(&status);
   exit(0); 
}
