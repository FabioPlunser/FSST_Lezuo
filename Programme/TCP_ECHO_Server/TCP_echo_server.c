#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h> 

#define Address "127.0.0.1"
#define Port 8080
#define BUFSIZE 100
#define Backlog 2

#define handle_error(msg) \  
    do { perror(msg); exit(EXIT_FAILURE); } while (0) // Error handler, directly copied from bind man page

char* encode(char* str) // RLE Encode
{    
    char* output = malloc(strlen(str));  //memory allocation
    char* count = malloc(strlen(str));

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


void* handle_connection(int clientfd)   //receives from client and sends
{   
    char* buf = malloc(BUFSIZE);    //reserve RAM
    char* output = malloc(BUFSIZE); 

    char* writing = "Please type a string, the server will return the RLE encoded string:\n";   //write what the client can do
    if (send(clientfd, writing , strlen(writing), 0) == -1){
            handle_error("send");
            close(clientfd);
    }
    
    
    while(1) 
    {
        int bytes_read = read(clientfd, buf, sizeof(buf)); //receive data from client.
        
        if (bytes_read == 0)
        {
            break; 
        } 
        
        buf[bytes_read-1] = 0;  //set EOS
        printf("Buf: %s\n", buf); //Print Buf

        char* rleresult = encode(buf); //get the result of the RLE

        printf("RLE: %s\n", rleresult); //print RLE result

        //Print Server answer with RLE Result
        output = "Server Answer:";
        if (send(clientfd, output, strlen(output), 0) == -1){
                handle_error("send");
                close(clientfd);
            }
        output = rleresult;
        strcat(output, "\n");
        if (send(clientfd, output, strlen(output), 0) == -1){
                handle_error("send");
                close(clientfd);
            }
        free(output);
    }
    close(clientfd);
}


int connection()
{   
    //Set all variables
    int socketfd, clientfd;
    struct sockaddr_in addr;
    memset(&addr, 0 , sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;  //set socket to use IPv4
    addr.sin_addr.s_addr = inet_addr(Address); //convert the string pointed to by cp, in the standard IPv4 dotted decimal notation, to an integer value suitable for use as an Internet address.
    addr.sin_port = htons(Port); //convert the unsigned short integer hostshort from host byte order to network byte order.
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0); //create socket 
    if (socketfd == -1){
        handle_error("socket");
    }
    if(bind(socketfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) == -1) //bind socket to properties
    {   
        handle_error("bind");
    }        
    
    printf("Started Socket at %s %i\n", Address, Port);

    if(listen(socketfd, Backlog) == -1) //listen for connections
    {
        handle_error("listen");
    }
    
    printf("Listening\n");
    socklen_t socklen = sizeof(addr);
    pthread_t thread_id;
    
    
    while ((clientfd = accept(socketfd, (struct sockaddr *)&addr, &socklen))) //accept connection of every user 
    {   
        printf("Client with IP %s connected, descriptor %i\n", inet_ntoa(addr.sin_addr), clientfd);
        if(clientfd < 0)
        {
            handle_error("accept");
            close(clientfd);
            return EXIT_FAILURE;
        }    
        
        if(pthread_create(&thread_id, NULL, handle_connection, clientfd) < 0) //create a new thread that handles the connection
        {
            handle_error("accept");
            close(clientfd);
            return EXIT_FAILURE;
        }   
    }
    return EXIT_FAILURE;
}

int main(int argc, char **argv)
{
    connection();    
}