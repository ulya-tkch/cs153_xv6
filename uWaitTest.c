// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

void
waitTest(void)
{
  int status, pid;

  printf(1, "starting child process...\n");
  pid = fork();
  if(pid < 0){
    printf(1, "fork error\n");
    exit(-1);
  }
  
  if(pid == 0){
    printf(1, "child forked successfully...\n");
    exit(22);
  } 
 // status = 777;
 // printf(1, " (777) write %d\n", status);
  
  if(wait(&status) < 0){
    printf(1, "wait error: no child created\n");
    exit(1);
  }
  printf(1, "child finished, status is: %d\n", status);
  
}

void
waitpidTest(void)
{
  int status, pid, w_pid;

  printf(1, "starting child process...\n");
  pid = fork();
  if(pid < 0){
    printf(1, "fork error\n");
    exit(-1);
  }
  
  if(pid == 0){ //child
    printf(1, "child forked successfully...\n");
    exit(33);
  }else{        //parent
    printf(1, "child created with PID: %d\n", pid);
  } 

  if((w_pid = waitpid(pid, &status, 0)) < 0){
    printf(1, "wait error: no child created\n");
    exit(1);
  }

  printf(1, "child finished with PID: %d ,status is: %d\n", w_pid, status);
  
}


int
main(void)
{
  waitTest();
  waitpidTest();
  exit(0);
}
