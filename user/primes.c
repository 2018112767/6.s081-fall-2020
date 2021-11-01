#include "kernel/types.h"
#include "user/user.h"

void func(int *input, int num)
{
    if(num==1)
    {
        printf("prime %d\n", *input);
		return;
    }
    int i;
    int p[2];
    int tp=*input;
    int tmp;
    printf("prime %d\n", *input);
    int cnt=0;
    char buffer[4];
    pipe(p);
    if(fork()==0)
    {
        //close(0); //大概是把管道的输出定位到标准输出里，子进程是管道右端
        //dup(p[0]);
        //close(p[0]);
        close(p[1]);
        while(read(p[0],buffer,4)!=0)
        {
            tmp=*((int *)buffer);
            if(tmp%tp)
            {
                *input=tmp;
                cnt++;
                input+=1;
            }
        }
        func(input-cnt,cnt);
        exit(0);
    }
    close(p[0]);
    for(i = 0; i < num; i++){
        tmp = *(input + i);
		write(p[1], (char *)(&tmp), 4);
    }
    close(p[1]);
    wait(0);
    exit(0);
}

int main()
{
    int i;
    int nums[36];
    for(i=2;i<=35;i++)
    {
        nums[i-2]=i;
    }
    func(nums,34);
    return 0;
}