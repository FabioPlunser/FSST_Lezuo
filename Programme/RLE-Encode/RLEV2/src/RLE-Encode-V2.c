// Author: FabioPlunser //
// Date: 21.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// RLE-Encode//

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RLEN 100

char* encode(char* str){
    
    char* string = str; 
    char* output = malloc(MAX_RLEN);  //memory allocation
    char* count = malloc(MAX_RLEN);

    int j, i, x = 0;

    for(i=0; *string != '\0'; i++){    
        
        *(output+i) = *string; //get first value of pointer string
        for(j=0; *string == *(output+i); j++){ // if value of string pointer is the same as output value go to next address
            string++;   //go to the next address --> next value of pointer string
        }
        sprintf(count, "%i", j); // write how often it counted till string == output+1 ==== False
        
        //*(output+(++i)) = *count; // At first i had this solution, but it only works with 1 digit numbers

        for (x =0; x<strlen(count); x++){ 
            *(output+(++i)) = *(count+x); // for values with more than 1 digit, 
        }
    }
    free(count); //deallocate count in memory
    *(output+(++i)) == '\0'; //add EOS 
    
    return output;
}

int main(int argc, char **argv){
    
    char str[MAX_RLEN];

    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL){
            break;
        }
        
        str[MAX_RLEN] = 0; 
        str[strlen(str)-1] = 0;

        char* res= encode(str);

        printf("Output>: %s\n", res);
        free(res);
    }
    while (strlen(str)>1);
    
}
