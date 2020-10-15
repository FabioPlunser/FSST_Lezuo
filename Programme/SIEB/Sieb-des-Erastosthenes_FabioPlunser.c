#include <stdio.h>



#define true 1
#define false 0

int prime_number(int MaxValue){
    int array[MaxValue];
    int i;
    int j;

    for (i=2; i<=MaxValue; i++){
        array[i] = false;           //set complete array zero. 0 and 1 are undefinded because the first prime number is 2
    }
    for (i=2; i<=MaxValue; i++){               
        if(array[i] == false){      
            printf("%d\n", i);
            
            for(j=i*i; j<=MaxValue; j=j+i){     //Go through every 0 value in array, and set every squared number 1, so it won't print it   
                array[j] = true;                //because it's it's no loner a prime number
            }
        }
    }
}
int main(){
    
    int MaxValue;
    printf("What maximum prime number you want? ");
    scanf("%i", &MaxValue);
    prime_number(MaxValue); 
    
    return 0;
}