#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p2c_fd[2];
    int c2p_fd[2];
    pipe(p2c_fd);//read[0] -> write[1]
    pipe(c2p_fd);
    int pid = fork();
    if(pid==0){
        close(p2c_fd[1]);
        close(c2p_fd[0]);
        char *rev_msg ="";
        char *send_msg = "c";
        while(strlen(rev_msg)==0){
            read(p2c_fd[0],rev_msg,1);
        }
        char mypid = getpid()+'0';
        write(1,&mypid,1);
        char * print_msg = ": received ping\n";
        write(1,print_msg,strlen(print_msg));
        close(p2c_fd[0]);
        write(c2p_fd[1],send_msg,1);
        close(c2p_fd[1]);
    }else {
        close(p2c_fd[0]);
        close(c2p_fd[1]);
        char *rev_msg ="";
        char *send_msg = "p";
        write(p2c_fd[1],send_msg,1);
        while(strlen(rev_msg)==0){
            read(c2p_fd[0],rev_msg,1);
        }
        wait(&pid);
        char mypid = getpid()+'0';
        write(1,&mypid,1);
        char *print_msg = ": received pong\n";
        write(1,print_msg,strlen(print_msg));
        close(p2c_fd[1]);
        close(c2p_fd[0]);
    }
    return 0;
}