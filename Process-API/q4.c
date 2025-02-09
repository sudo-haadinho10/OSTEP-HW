#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc,char *argv[]){
    int rc=fork();
    
    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    if(rc==0){
        //start child process
        char *myArgs[2];
        myArgs[0]=strdup("/bin/ls");
        myArgs[1]=NULL;
        

        char * myEnvp[2];
        myEnvp[0]="STDOUT_FILENO";
        myEnvp[1]=NULL;
        execle(myArgs[0], "/ls", NULL, myEnvp);
        //execvp(myArgs[0],myArgs);
        //execv(myArgs[0],myArgs);
        //execvpe(myArgs[0],myArgs,myEnvp); 
    }
    else{
        int rc_wait=wait(NULL);
        printf("\nNow in Parent Process\n");
    }
}

//NOTE : 
        //All other exec() functions (which do not include 'e' in the suffix) 
        //take the environment for the  new  process
       //image from the external variable environ in the calling process.
