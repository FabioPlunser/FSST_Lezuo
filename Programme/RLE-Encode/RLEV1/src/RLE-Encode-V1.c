#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 100


char* encode(char* str)
{
    char* string = str;
    int count=1;
    char *output;
    char character = '0';

    int j, i;

    printf("\n%s\n",str);

    for (i = 0; i<=strlen(string)-1; i++)
    {
        character = string[i];
        
        for(j = i+1; j<=strlen(string); j++) 
        {
            if(string[j] == character)
            {
                count++;
                i++;
            }else
            {
                sprintf(output, "%c %i\n", character, count);
                count=1;
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
