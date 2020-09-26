#include <ctype.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int isvalidport(char *port);
int isvalidip(char *ip_addr);

/* Store IP address string in sockaddr_in struct:
 * inet_pton(AF_INET "192.168.0.1", &(sa.sin_addr));
 */

int main(int argc, char **argv) {
    char *ip_addr = NULL;
    char *port = NULL;
    int index;
    int c;

    opterr = 0;
    
    if (argc == 0) {
        // set to server
    }
    else {
        // handle arguments
    }
    while ((c = getopt(argc, argv, "hp:s:")) != -1)
        switch(c) {
            case 'h':
                // print help message
                printf("Help Message\n");
                return 0;
            case 's':
                ip_addr = optarg;
                printf("ip address: %s\n", ip_addr);
                if (isvalidip(ip_addr))
                    printf("IP is valid\n");
                else
                    printf("IP is not valid\n");
                // verify valid input
                break;
            case 'p':
                port = optarg;
                printf("port: %s\n", port);
                if (isvalidport(port))
                    printf("Port is valid\n");
                else
                    printf("Port is not valid\n");
                // verify valid input
                //
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
	return 0;
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
