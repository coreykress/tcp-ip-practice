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

    //server socket address struct
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //bind -> binds name to a socket sockfd is socket, serv_addr is address (this accepts pointer to it), and then address length
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error('Error on binding');
    }

    //make socket (sockfd) passive(accept incoming connections) and accept a limit of 5 connections
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    //accept a connection on a new socket
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) {
        error('Error on connect');
    }

    bzero(buffer, 256);
    //read 255 bytes from newsockfd into the buffer
    n = read(newsockfd,buffer,255);

    if (n < 0) {
        error('Error reading into buffer');
    }

    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) {
        error("ERROR writing to socket");
    }

    return 0;

}