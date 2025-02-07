#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){
    int rc=fork();

    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    else if(rc==0){
        //child process start
        close(1); //close file descriptor 1
        printf("Random Output\n");
        printf("Done with child process(pid:%d)\n",getpid());
    }
    else{
        int rc_wait=wait(NULL);
        printf("Now in parent process(pid:%d) of child(pid:%d)\n",getpid(),rc_wait);
    }
}

//1)    What happens if the child calls printf() to print some output after closing the descriptor?
//Ans:  It get's ignored/will not be displayed.
