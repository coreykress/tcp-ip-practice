#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error (char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    //declare vars
    int sockfd, newsockfd, portno, clilen;

    char buffer[256];

    struct sockaddr_in serv_addr, cli_addr;

    int n;

    if (argc < 2) {
        fprintf(stderr, 'ERROR no port provided \n');
        exit(1);
    }

    //socket(ivp4 protocols, stream socket(tcp)) -> this is communication endpoint
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error('Issue opening socket');
    }

    //bzero -> write zero valued bytes
    /*
     * *var or type * is a memory address
     * in the memory address for serv_addr, set all bytes to 0
     *
     */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
}