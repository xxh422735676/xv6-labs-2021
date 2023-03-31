#include "kernel/types.h"
#include "user/user.h"

// int strlen(const char * str){
//     int i = 0;
//     for(char ch = str[i];ch!='\0';i++)
//     return i;
// }
int main(int argc, char **argv)
{
    if(argc==2){
        sleep(atoi(argv[1]));
        write(1,argv[1],strlen(argv[1]));
        const char *msg = "success on args!\n";
        write(0,msg,18);
    }
    else {
        // const char *msg = "error on args!\n";
        // write(1,msg,strlen(msg));
    }
    return 0;
}