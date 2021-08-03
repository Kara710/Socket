#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8000
#include <iostream>     // std::cin, std::cout
 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Communicate(int &socket){
	char buffer[256];
	 
	while(1){
		bzero(buffer,256);
		read(socket,buffer,255);
		printf("Client: %s\n",buffer);
 
		bzero(buffer,256);
		std::cout<<"Server:";
		std::cin.getline (buffer, 256);
		write(socket,buffer,256);
		 
	}
	
}

int main()
{
     int sockfd, newsockfd;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
  
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
	 clilen = sizeof(cli_addr);
 
	newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
    Communicate(newsockfd);
	
     close(newsockfd);
     close(sockfd);
     return 0; 
}
