#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int i;
    int j=0;
    int len;
    char *lin[32];
    char block[33];
    char *p;
    for(i=1;i<argc;i++)
    {
        lin[j++]=argv[i];
    }
    while((len=read(0,block,sizeof(block)-1))>0)
    {
        p=block;
        for(i=0;i<len;i++)
        {
            if(block[i]==' ')
            {
                block[i]=0;
                lin[j++]=p;
                p=&block[i+1];
            }
            else if(block[i]=='\n')
            {
                block[i]=0;
                lin[j++]=p;
                p=&block[i+1];
                lin[j]=0; //示意参数结束
                j=argc-1; //去除argv[0]
                if(fork()==0)
                {
                    exec(argv[1],lin);
                }
                wait(0);
            }
        }
    }
    exit(0);
}