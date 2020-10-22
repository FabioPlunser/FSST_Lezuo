// Author: FabioPlunser //
// Date: 21.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/RLE-Encode/RLEV2/src/RLE-Encode-V2.c//
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// RLE-Encode Version2//

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RLEN 100

char* encode(char* str){
    
    
    char* output = malloc(MAX_RLEN);  //memory allocation
    char* count = malloc(MAX_RLEN);

    int j, i, x = 0;

    for(i=0; *str != '\0'; i++){    
        
        *(output+i) = *str; //get first value of pointer string
        for(j=0; *str == *(output+i); j++){ // if value of string pointer is the same as output value go to next address
            str++;   //go to the next address --> next value of pointer string
        }
        sprintf(count, "%i", j); // write how often it counted till string == output+1 ==== False
        
        //*(output+(++i)) = *count; // At first i had this solution, but it only works with 1 digit numbers

        for (x =0; x<strlen(count); x++){ 
            *(output+(++i)) = *(count+x); // for values with more than 1 digit because 2nd digit is in third address, 
        }
    }
    free(count); //deallocate count in memory
    return output;
}

int main(int argc, char **argv){
    
    char str[MAX_RLEN];

    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL){
            break;
        }
        
        str[MAX_RLEN] = 0;      //don't really know how this works, shouldn't do anything because of wron syntax? But can compile char array[100] = {0};
                                //doesn't make sens to set all values to zero after getting the string if fgets 
        str[strlen(str)-1] = 0; //neded to ensure the correct size of string, strlen returns 
                                //real string length + 1 because the nul terminator gets registered as a chrakter

        char* res= encode(str);

        printf("Output>: %s\n", res);
        // free(res);  does not get allocated so no point of delacoation
    }
    while (strlen(str)>1);
    
}
