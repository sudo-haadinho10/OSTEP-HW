#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){
    int rc = fork();

    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    if(rc==0){
        //child process start
        printf("hello\n");
    }
    else{
        sleep(3); //       sleep - sleep for a specified number of seconds
        printf("goodbye\n");
    }
}
