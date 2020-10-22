
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 100


char* encode(char* str)
{
    char* output = malloc(MAX_RLEN);
    char* temp = malloc(MAX_RLEN);
    char character = '0';
    int j, i, z = 0;
    int icount = 1;

    for (i = 0; i<=strlen(str)-1; i++)
    {
        character = str[i];

        for(j = i+1; j<=strlen(str); j++) 
        {
            if(str[j] == character)
            {
                icount++;
                i++;
            
            }else
            {
                sprintf(temp, "%c%i", character, icount);
                
                *(output+(z++)) = *(temp);
                *(output+(z++)) = *(temp+1);
                
                if (icount >= 10 ){
                    *(output+z) = *(temp+2);
                }
                icount=1;
                break;
            }
 
        }  
    }
    free(temp);
    *(output+(i)) == '\0';

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