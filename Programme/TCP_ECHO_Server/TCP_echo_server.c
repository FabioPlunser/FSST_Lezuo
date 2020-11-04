#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_PATH ""
#define Address "127.0.0.1"
#define Port 3500
#define BUFSIZE 32
#define Backlog 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main()
{
    printf("hallo");
    //from bind man Page exampel
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(Address);
    addr.sin_port = htons(Port);

    memset(&addr, 0 , sizeof(struct sockaddr_in));

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1){
        printf("Socket could not me created");
        handle_error("socket");
    }
    if(bind(socketfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) == -1)
    {   
        printf("schlecht");
        handle_error("bind");
    }
        
    
    printf("Started Socket at %s %i", Address, Port);

    if(listen(socketfd, Backlog) == -1)
    {
        printf("schlecht2");
        handle_error("listen");

    }
    
    // socklen_t address_len = sizeof(struct sockaddr_in);
    
    int acceptfd = accept(socketfd, (struct sockaddr*) &addr, &address_len);
    if(acceptfd == -1)
        handle_error("accept");

    if (send(socketfd, "hello", 5, 0) == -1){
        handle_error("send");
        close(socketfd);
        return EXIT_FAILURE;
    }
    
}