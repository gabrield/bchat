#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 3310

int main()
{

    const char *mess = "HELLO BROADCAST";
    struct sockaddr_in s;

    int bcast_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int broadcastEnable = 1;
    int ret = setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));


    if(bcast_sock < 0)
        return;

    memset(&s, '\0', sizeof(struct sockaddr_in));
    s.sin_family = AF_INET;
    s.sin_port = (in_port_t)htons(PORT);
    s.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    if(sendto(bcast_sock, mess, strlen(mess), 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
        perror("sendto");
   return 0;
}
