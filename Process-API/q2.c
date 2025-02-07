#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine)(void *), void *arg);

typedef struct{
    char *string;
    int length;
    int fd;
} ThreadsArgs;

void* writeThread(void * arg){
    ThreadsArgs *args = (ThreadsArgs *)arg;
    write(args->fd,args->string,args->length);
}


int main(int argc,char* argv[]){
    int fd = open("file1.txt", O_WRONLY | O_CREAT |O_TRUNC,S_IRWXU );
    int rc=fork();
    pthread_t p1,p2; //thread identifier

    if(rc<0){
        fprintf(stderr,"fork failed\n");
    }
    if(rc==0){
        //child process starts
        assert(fd>-1); //       assert - abort the program if assertion is false
        printf("for child process(%d), fd is accessible\n",getpid());
        ThreadsArgs args1 = {"  Child TRADEMARK",17,fd};
        pthread_create(&p1,NULL,writeThread,&args1);



    }
    else{
        //int rc_wait=wait(NULL);
        assert(fd>-1);
        printf("for parent process(%d) of child(%d), fd is accessible\n",getpid(),rc);
        ThreadsArgs args1 = {"  Parent TRADEMARK",18,fd};
        pthread_create(&p2,NULL,writeThread,&args1);
    }
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);


    return 0;

}
