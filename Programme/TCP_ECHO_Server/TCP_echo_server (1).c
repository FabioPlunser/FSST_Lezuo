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
#define Port 1234
#define BUFSIZE 32
#define Backlog 2

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

char* encode(char* str)
{    
    
    char* output = malloc(BUFSIZE);  //memory allocation
    char* count = malloc(BUFSIZE);

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


void* handle_connection(int clientfd)
{   
    char* writing = "Please type a string, the server will return the RLE encoded string:\n";
    if (send(clientfd, writing ,strlen(writing), 0) == -1){
            handle_error("send");
            close(clientfd);
        }
    char buf[BUFSIZE]; 
    char* output = malloc(BUFSIZE);
    int bytes_read;
    
    

    while((strcmp(buf, "close") != 0) || strcmp(buf, "") != 0) 
    {
        while ((bytes_read = read(clientfd, buf, sizeof(buf))) > 0 )
        {
            if(bytes_read > BUFSIZE-1 || buf[bytes_read-1] == '\n') break; 
        }
        buf[bytes_read-1] = 0;
        printf("Buf: %s\n", buf);

        char* rleresult = encode(buf);

        printf("RLE: %s\n", rleresult);

        
        output = "Server Answer:";
        if (send(clientfd, output ,strlen(output), 0) == -1){
                handle_error("send");
                close(clientfd);
            }
        output = rleresult;
        strcat(output, "\n");
        if (send(clientfd, output ,strlen(output), 0) == -1){
                handle_error("send");
                close(clientfd);
            }
        free(output);
    }
    
    char* closing = "By client, connection is getting closed\n";
    if (send(clientfd, closing ,strlen(closing), 0) == -1){
            handle_error("send");
            close(clientfd);
        }
    
    close(clientfd);
}



int connection()
{   
    int socketfd, clientfd;
    struct sockaddr_in addr;
    memset(&addr, 0 , sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(Address);
    addr.sin_port = htons(Port);
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1){
        printf("Socket could not me created");
        handle_error("socket");
    }
    if(bind(socketfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) == -1)
    {   
        handle_error("bind");
    }        
    
    printf("Started Socket at %s %i\n", Address, Port);

    if(listen(socketfd, Backlog) == -1)
    {
        printf("schlecht2");
        handle_error("listen");
    }
    printf("Listening\n");
    socklen_t socklen = sizeof(addr);
    pthread_t thread_id;
    
    
    while ((clientfd = accept(socketfd, (struct sockaddr *)&addr, &socklen)))
    {   
        printf("Accepted connection\n");


        printf("Client with IP %s connected, descriptor %i\n", inet_ntoa(addr.sin_addr), clientfd);
        if(clientfd < 0)
        {
            handle_error("accept");
            close(clientfd);
            return EXIT_FAILURE;
        }    
        
        if(pthread_create(&thread_id, NULL, handle_connection, clientfd) < 0)
        {
            handle_error("accept");
            close(clientfd);
            return EXIT_FAILURE;
        }   
    }
    return EXIT_FAILURE;
}

int main()
{
    connection();
}