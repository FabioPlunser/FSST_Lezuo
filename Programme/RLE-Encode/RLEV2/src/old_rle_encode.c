#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 100


char* encode(char* str)
{
    char* string = str;
    char* output = malloc(MAX_RLEN);
    char* count = malloc(MAX_RLEN);

    int j, i = 0;
    int icount = 1;

    printf("\n%s\n",str);

    for (i = 0; i<=strlen(string)-1; i++)
    {
        *(output+i) = *string;
        for(j = i+1; j<=strlen(string); j++) 
        {
            
            if(*string == *output)
            {
                
                icount++;
                i++;
                string++;
            
            }else
            {
                sprintf(count, "%i", icount);
                *(output+(++i)) = *count;  
                icount=1;
                break;
            }
             
        } 
         
        
    }
    return output;
    
}

int main(int argc, char **argv)
{
    char str[MAX_RLEN]; 
    
    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL)
        {
            printf("Empty String");
            break;
        } 

        str[MAX_RLEN] = 0;  // --> '\0'
        str[strlen(str)-1] = 0;

        char* res = encode(str);

        printf(">: %s\n", res);
        free(res);
    }
    while (strlen(str) > 1);
}