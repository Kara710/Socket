#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define PORT 8000
#include <iostream>     // std::cin, std::cout

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void Communicate(int &socket){
	char buffer[256];

	while(1){
		bzero(buffer,256);
 		std::cout<<"Client:";
		std::cin.getline (buffer, 256);
		write(socket,buffer,strlen(buffer));
	 
		bzero(buffer,256);
		read(socket,buffer,255);
		 
		printf("Server: %s\n",buffer);
	}


}

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr;
 
    char buffer[256];
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
     
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
	
	
	
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
  
	Communicate(sockfd);
	
    close(sockfd);
    return 0;
}