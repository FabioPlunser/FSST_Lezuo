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
int i=0;
void** create_search_index()
{
    int wortbuffer, read_length;
    void* BFBuffer = malloc(BFBuffer_Size); 

    wortbuffer = open("wortbuffer", O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    
    printf("Make List\n");
    void** search_index = malloc(read_length);
    search_index[i] = BFBuffer;
    
    for(int x=0; x<read_length; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            search_index[++i] = BFBuffer+(++x);
            // printf("%s, %i\n", (char*)search_index[i], i)
            
        }
        
    }
    return search_index;
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


//recursive
void* compare(char* input, void** search_index, int number_of_words)
{   
    // printf("Hallo: %s\n", *((char**)search_index));
    printf("numwords: %i\n", number_of_words);
    if (diff > 0 )
    {
        search_index += (number_of_words);
        diff = strcmp(input, *((char**)search_index));
        printf("compare: %s, with: %s\n", input, *((char**)search_index));
        printf("diff1: %i\n", diff);
    }
    else if(diff < 0)
    {
        search_index -= (number_of_words);
        diff = strcmp(input, *(char**)search_index);
        printf("compare: %s, with: %s\n", input, *((char**)search_index));
        printf("diff2: %i\n", diff);
    }
    else 
    {
        printf("Ergebniss: %s\n", *((char**)search_index));
        
        return *search_index;
    }
    if(number_of_words == 0)
    {
        if(strcmp(input, *((char**)search_index-1)) == 0)
        {
            printf("Ergebniss: %s\n", *((char**)search_index));
            return *search_index;
        }
        else if(strcmp(input, *((char**)search_index+1)) == 0)
        {
            printf("Ergebniss: %s\n", *((char**)search_index));
            return *search_index;
        }
        else
        {
        printf("Letze Wort: %s\n", *((char**)search_index-10));
           return NULL;
        }
    }
    return compare(input, search_index, number_of_words/2);    //recursive loop
    // if (diff > 0)   //if input bigger than BFBuffer go right to a bigger word in Buffer
    // {
    //     BFBuffer+=(BFBuffer_Size/i); //go to the half of the half of the half of the half of the half and eventually found word
    //     while(*((char*)BFBuffer-1) != 0){
    //         BFBuffer++; //"go" right
    //     }

    //     diff = strcmp(input, (char*)BFBuffer); //compare new word with input word
    //     i = i*2; //set new half of halt
    // }
    // else
    // {
    //     BFBuffer-=(BFBuffer_Size/i);    //all the same as the top but go to left if input is smaller than actual word in Buffer
    //     while(*((char*)BFBuffer-1) != 0){
    //         BFBuffer--;
    //     }

    //     diff = strcmp(input, (char*)BFBuffer);
    //     i = i*2;
    // }
    // printf("%s\n", (char*)BFBuffer);
    
    // if(diff == 0) //if input word and Buffer word are the same reset variables and return word from buffer
    // {
    //     diff = 1;
    //     i = 2;
    //     return BFBuffer;
    // }
    // if(i>BFBuffer_Size) return NULL; //catch overflow if word is not in Buffer

    
}



int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        void** search_index = create_search_index(); //get wordfile into a very big buffer
        printf("Erste Stelle: %s\n", *((char**)search_index));
        printf("Main: %i\n", i);
        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before finding word
        
        void* res = compare(input, search_index, i/2);
        

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