  #include <communication.h>
  
Communication::Communication(int port)
{
  
  slen = sizeof(cli_addr);
  
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    perror("socket");
  else 
    printf("Server : Socket() successful\n");
  
  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
  {
    perror("bind");
    exit(0);
  }
  else
    printf("Server : bind() successful\n");
    
    
  //SENDER SECTION
  
  bcast_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  broadcastEnable = 1;
  ret = setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));


  if(bcast_sock < 0)
      return;

  memset(&send_addr, '\0', sizeof(struct sockaddr_in));
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = (in_port_t)htons(port);
  send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);  
}
  
  
  
  char *Communication::Listen()
  {
      memset((void*)buf, 0, 1024);
      if (recvfrom(sockfd, buf, 1024, 0, (struct sockaddr*)&cli_addr, &slen) == -1)
        perror("recvfrom()");
        
      //printf("Received packet from %s:%d\nData: %s\n\n",
      //       inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);
      return buf;
  }
  
  
  void Communication::Send(const char *msg){

  if(sendto(bcast_sock, msg, strlen(msg), 0, (struct sockaddr *)&send_addr, sizeof(struct sockaddr_in)) < 0)
    perror("sendto");
    
  }
  
  
  ~Communication::Communication()
  {
    close(sockfd);
    close(bcast_sock);
  }
  
  
  
