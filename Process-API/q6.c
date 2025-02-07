#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){
    int status,rc_wait;
    int rc=fork();

    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    else if(rc==0){
        
        //rc_wait=waitpid(rc,&status,WUNTRACED|WNOHANG);
        //printf("return value of rc_wait is : %d\n",rc_wait);

        printf("hello from child (pid:%d)\n",getpid());
        _exit(2);
    }
    else{
        
        rc_wait=waitpid(rc,&status,WUNTRACED);


        if(WIFEXITED(status)){
            printf("return value of waitpid() is:%d\n",rc_wait);
            printf("normal termination of child ,exit status=%d\n",WEXITSTATUS(status));
        }
        
        printf("goodbye from parent (pid:%d)\n",getpid());
    }
    return 0;

}
