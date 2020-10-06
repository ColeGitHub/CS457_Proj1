#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define PORT "3490"

int parseargs(int argc, char **argv, char *ip_addr, char *port);
int isvalidport(char *port);
int isvalidip(char *ip_addr);
int start_server(void);

/* Store IP address string in sockaddr_in struct:
 * inet_pton(AF_INET, "192.168.0.1", &(sa.sin_addr));
 */

int main(int argc, char **argv) {
    char *ip_addr = NULL;
    char *port = NULL;
    int c;

    opterr = 0;
    
    if (argc == 1) {
        // set to server
        printf("This is a server\n");
    }
    else {
        // handle arguments
        if(parseargs( argc, argv, ip_addr, port ) == 1) {
            return 1;
        }
        printf("This is a client\n");
    }
    printf("IP: %s\n", ip_addr);
    printf("Port: %s\n", port);
	return 0;
}

int parseargs(int argc, char **argv, char *ip_addr, char *port) {
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "hp:s:")) != -1) {
        switch(c) {
            case 'h':
                // print help message
                printf("Help Message\n");
                return 0;
            case 's':
                ip_addr = optarg;
                printf("ip address: %s\n", ip_addr);
                if (isvalidip(ip_addr)) {
                    printf("IP is valid\n");
                }
                else {
                    printf("IP is not valid\n");
                    return 1;
                }
                break;
            case 'p':
                port = optarg;
                printf("port: %s\n", port);
                if (isvalidport(port)) {
                    printf("Port is valid\n");
                }
                else {
                    printf("Port is not valid\n");
                    return 1;
                }
                break;
            case '?':
                if (optopt == 's' || optopt == 'p')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
                return 1;
            default:
                printf("No arguments provided\n");
                abort();
        }
    }
}

int isvalidport(char *port) {
    int s = strlen(port);
    for (int i = 0; i < s; i++) {
        if (!isdigit(*port))
            return 0;
        port++;
    }
    return 1;
}

int isvalidip(char *ip_addr) {
    int s = strlen(ip_addr);
    for (int i = 0; i < s; i++) {
        if (!isdigit(ip_addr[i]) && ip_addr[i] != '.') 
            return 0;
    } 
    return 1;
}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*int start_server(void) {
    int sockfd, new_fd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's addr
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET_ADDRSTRLEN]
    int rv;

    memset(&hints, 0, sizeof hints);
    hint.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    } 

    for (p = servinfo; p != NULL; p = p->ai_next) {

    }

}*/
