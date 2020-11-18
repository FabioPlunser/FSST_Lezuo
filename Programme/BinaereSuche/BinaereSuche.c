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

#define BFBuffer_Size 500000

int diff = 1;
int i = 2;

void* create_buffer() //write word file in buffer, just read 5 million bytes. 
{
    int wortbuffer, read_length;
    void* BFBuffer = malloc(BFBuffer_Size); //reserve big fucking buffer

    wortbuffer = open("wortbuffer", O_RDONLY); 
    if (wortbuffer == -1)
    {
        perror("open");
    }
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size);
    return BFBuffer;
}

void* compare(char* input, void* BFBuffer) //compare buffer with input
{
    diff = strcmp(input, BFBuffer);
    
    while(diff != 0) //as long as input string is not buffer string do following
    {
        if (diff > 0)  // if strcmp is bigger than 0 than input is bigger than buffer, so need to go higher in the buffer to be the same
        {
            BFBuffer+=(BFBuffer_Size/i); // binary search, go from zero to the middle and go to a higher string, at half of before
            if(((char*)BFBuffer-1) != 0){
                BFBuffer++;
            }

            diff = strcmp(input, BFBuffer); 
            i = i*2; //multiply by two to get to the half of the half
        }
        else if (diff < 0) // if strcmp less than 0, need to go left or lower in the buffer
        {
            BFBuffer-=(BFBuffer_Size/i); // binary search, go from zero to the middle and go to a lower string, at half of before
            if(((char*)BFBuffer-1) != 0){
                BFBuffer--;
            }

            diff = strcmp(input, BFBuffer);
            i = i*2; //multiply by two to get to the half of the half
        }
        printf("%s\n", (char*)BFBuffer);
        if(i>sizeof(BFBuffer)) return NULL; //because some words are not in it, need to catch int overflow
        compare(input, BFBuffer); //recursive
        
    }
    return BFBuffer; //return BFBuffer, now it should only have the searched word in it
}

int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        void* BFBuffer = create_buffer(); //get wordfile in buffer in function create buffer

        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before searching 
        void* res = compare(input, BFBuffer); //get result if input is in BFBuffer
        gettimeofday(&tv_begin, NULL); //get time after searching

        timersub(&tv_end, &tv_begin, &tv_diff); // subtract time before with time after to get how long it took

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