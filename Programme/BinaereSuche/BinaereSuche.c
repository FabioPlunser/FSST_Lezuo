// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// BinaereSuche //

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
    
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    return BFBuffer;
}

// not recursive
// void* compare(char* input, void* BFBuffer)
// {
//     int diff = 1;
//     int i = 2;
//     while(diff !=0)
//     {
//         if (diff > 0)
//         {
//             BFBuffer+=(BFBuffer_Size/i);
//             while(*((char*)BFBuffer-1) != 0){
//                 BFBuffer++;
//             }

//             diff = strcmp(input, (char*)BFBuffer);
//             i = i*2;
//         }
//         else
//         {
//             BFBuffer-=(BFBuffer_Size/i);
//             while(*((char*)BFBuffer-1) != 0){
//                 BFBuffer--;
//             }

//             diff = strcmp(input, (char*)BFBuffer);
//             i = i*2;
//         }
//         printf("%s\n", (char*)BFBuffer);
//         if(i>BFBuffer_Size) return NULL;
//     }
//     return BFBuffer;
// }

//revursive
void* compare(char* input, void* BFBuffer)
{
    if (diff > 0)   //if input bigger than BFBuffer go right to a bigger word in Buffer
    {
        BFBuffer+=(BFBuffer_Size/i); //go to the half of the half of the half of the half of the half and eventually found word
        while(*((char*)BFBuffer-1) != 0){
            BFBuffer++; //"go" right
        }

        diff = strcmp(input, (char*)BFBuffer); //compare new word with input word
        i = i*2; //set new half of halt
    }
    else
    {
        BFBuffer-=(BFBuffer_Size/i);    //all the same as the top but go to left if input is smaller than actual word in Buffer
        while(*((char*)BFBuffer-1) != 0){
            BFBuffer--;
        }

        diff = strcmp(input, (char*)BFBuffer);
        i = i*2;
    }
    printf("%s\n", (char*)BFBuffer);
    
    if(diff == 0) //if input word and Buffer word are the same reset variables and return word from buffer
    {
        diff = 1;
        i = 2;
        return BFBuffer;
    }
    if(i>BFBuffer_Size) return NULL; //catch overflow if word is not in Buffer

    return compare(input, BFBuffer);    //recursive loop
}



int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        void* BFBuffer = create_buffer(); //get wordfile into a very big buffer
        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before finding word
        
        void* res = compare(input, BFBuffer);
        

        gettimeofday(&tv_begin, NULL); //get time after finding word

        timersub(&tv_end, &tv_begin, &tv_diff); //subtract times to get the time how long it took

        if(res != NULL)
        {
            printf("found");
        }
        else
        {
            printf("not found");
        }
        printf(" in (%li seconds %li  microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);   //print time
    }
}