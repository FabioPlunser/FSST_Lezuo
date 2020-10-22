// Author: FabioPlunser //
// Date: 21.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo //
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/RLE-Encode/RLEV1/src/RLE-Encode-V1.c //
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// RLE-Encode Version1//

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 100


char* encode(char* str)
{
    char* output = malloc(MAX_RLEN); //memory allocation
    char* temp = malloc(MAX_RLEN);
    char character = '0';
    int j, i, z = 0;
    int icount = 1;

    for (i = 0; i<=strlen(str)-1; i++) 
    {
        character = str[i]; //get each chracter of the string at once

        for(j = i+1; j<=strlen(str); j++) 
        {
            if(str[j] == character) //Checks how often one specific charakter is in the string        {
                icount++;
                i++;
            
            }else
            {
                sprintf(temp, "%c%i", character, icount); //for outputting, put results in char*
                
                *(output+(z++)) = *(temp); //charakter to output
                *(output+(z++)) = *(temp+1); //count to output
                
                if (icount >= 10 ){ //of count is higher than 10 the second digit of the count is in the next address
                    *(output+z) = *(temp+2);
                }
                icount=1;
                break;
            }
        }  
    }
    free(temp)

    return output;
}

int main(int argc, char **argv)
{
    char str[MAX_RLEN]; 
    
    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL)
        {
            break;
        } 

        str[MAX_RLEN] = 0;  //don't really know how this works, shouldn't do anything because of wron syntax? But can compile char array[100] = {0};
                            //doesn't make sens to set all values to zero after getting the string if fgets 
        str[strlen(str)-1] = 0; //neded to ensure the correct size of string, strlen returns 
                                //real string length + 1 because the nul terminator gets registered as a chrakter

        char* res = encode(str);

        printf(">: %s\n", res);
        // free(res) does not get allocated so no point of delacoation
    }
    while (strlen(str) > 1);
}