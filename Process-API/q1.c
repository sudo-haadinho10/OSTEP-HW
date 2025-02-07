#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int x=100;

int main(int argc,char* argv[]){
    int rc=fork();

    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    else if(rc==0){
        //child new process
        printf("child (pid:%d)\n",(int) getpid());
        printf("value of x in child process:%d\n",x);
        x=125;
        printf("value of x in child process:%d\n",x);
    }
    else{
        int rc_wait = wait(NULL); //wait for the child process to complete
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",rc, rc_wait, (int) getpid());
        printf("value of x in parent process:%d\n",x);
        x=225;
        printf("value of x in parent process:%d\n",x);
    }
}
