// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/tree/main/Programme/TCP_ECHO_Server //
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// TCP-Echo-server //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h> 
#include <fcntl.h>

#define BFBuffer_Size 5000000

int diff = 1;
int i = 2;

void* create_buffer()
{
    int wortbuffer, read_length;
    void* BFBuffer = malloc(BFBuffer_Size);

    wortbuffer = open("wortbuffer", O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size);
    return BFBuffer;
}


void* compare(char* input, void* BFBuffer)
{
    
    
    if (diff > 0)
    {
        BFBuffer+=(BFBuffer_Size/i);
        while(*((char*)BFBuffer-1) != 0){
            BFBuffer++;
        }

        diff = strcmp(input, (char*)BFBuffer);
        i = i*2;
    }
    else
    {
        BFBuffer-=(BFBuffer_Size/i);
        while(*((char*)BFBuffer-1) != 0){
            BFBuffer--;
        }

        diff = strcmp(input, (char*)BFBuffer);
        i = i*2;
    }
    printf("%s\n", (char*)BFBuffer);
    
    if(diff == 0)
    {
        diff = 1;
        i = 2;
        return BFBuffer;
    }
    if(i>BFBuffer_Size) return NULL;

    return compare(input, BFBuffer);
}



int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        void* BFBuffer = create_buffer();
        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL);
        
        void* res = compare(input, BFBuffer);
        
        // void* res = compare(input);

        gettimeofday(&tv_begin, NULL);

        timersub(&tv_end, &tv_begin, &tv_diff);

        if(res != NULL)
        {
            printf("found");
        }
        else
        {
            printf("not found");
        }
        printf(" in (%li seconds %li  microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);   
    }
}