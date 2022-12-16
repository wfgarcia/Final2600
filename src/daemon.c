#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    // Fork the process and exit the parent process
    pid_t pid = fork();
    if (pid > 0) {
        exit(0);
    }

    // Create a server socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Bind the socket to port 8080
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept incoming connections and print out any data received
    while (1) {
        int clientfd = accept(sockfd, NULL, NULL);
        if (clientfd < 0) {
            perror("Error accepting connection");
            continue;
        }

        char buffer[256];
        int n = read(clientfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            close(clientfd);
            continue;
        }

        printf("Received: %s\n", buffer);
        close(clientfd);
    }

    return 0;
}
