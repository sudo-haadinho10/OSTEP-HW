#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){

    //Create two children
    //Connect stdOUT of rc1 to stdIN of rc2 using pipe() system call

    int pipefd[2]; // pipefd is used to return two file descriptors referring to the ends of the pipe.
     
    pid_t c1,c2;
    char buf;

    if(pipe(pipefd)==-1){
        perror("fork");
        _exit(EXIT_FAILURE);
    }
    c1=fork();
    if(c1<0){
        fprintf(stderr,"fork failed\n");
    }
    else if(c1==0){
        close(pipefd[0]); //close unused read end
        dup2(pipefd[1],STDOUT_FILENO);  //       int dup2(int oldfd, int newfd);
        close(pipefd[1]);
        char message[]="hello world from child 1";
        write(STDOUT_FILENO,message,sizeof(message)-1);
        _exit(EXIT_SUCCESS);
        }    
    else{
        c2=fork();
        if(c2<0){
            fprintf(stderr,"fork failed");
        }
        else if(c2==0){
            close(pipefd[1]);
            dup2(pipefd[0],STDIN_FILENO);
            close(pipefd[0]);
            //Now, using STDIN_FILENO, but it's redirected from pipefd[0]
            while(read(STDIN_FILENO,&buf,1)>0){ //read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
               write(STDOUT_FILENO,&buf,1);
            }
            write(STDOUT_FILENO,"\n",1);
    }
    else{
        close(pipefd[0]);
        close(pipefd[1]); //close unused write
        waitpid(c1,NULL,0);
        waitpid(c2, NULL,0);
    }   
}
    return 0;
}
