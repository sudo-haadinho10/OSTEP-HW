#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
    int rc=fork();
    
    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    if(rc==0){

        //For part2 of the question remove the multi line comments below

        /*
        int rc_wait=wait(NULL);
        printf("The value returned by wait:%d\n",rc_wait);
        */
        printf("hello from the child(pid:%d)\n",getpid());
    }
    else{
        
        //For part1 of the question remove the multiline comments below 

        /* 
        int rc_wait=wait(NULL); 
        //NULL indicates we are not interested in getting detailed info abt childs termination status
        printf("value returned by wait:%d\n",rc_wait);
        */ 
       
        printf("goodbye from parent(pid:%d)\n",getpid());
        
    }
}

/*
1) What does wait() return?

Ans: On success, it returns the process ID of the terminated child.

2)What happens if you use wait() in the child?

Ans: It returns -1,indicating a failure.
    As wait() is designed to wait for state changes in child processes of the calling process, 
    but here as the child has no further child process,wait() call fails.

*/
