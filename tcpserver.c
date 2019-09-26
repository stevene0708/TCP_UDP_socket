#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnumber 5555

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr, client_addr;	
	int sock, byte_recv, byte_sent, server_addr_length = sizeof(server_addr), client_addr_length = sizeof(client_addr), recfd;
	char buffer[50], buffer_1[] = "welcome!\0";
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Error creating socket\n");
	bzero(&server_addr, server_addr_length);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&server_addr, server_addr_length) == -1){
		printf("error binding!\n");
		close(sock);
	}
	if (listen(sock, 20) == -1){
		printf("listen failed!\n");
		close(sock);
	}
	if ((recfd = accept(sock, (struct sockaddr *)&client_addr, &client_addr_length)) == -1){
		printf("accept failed!\n");
		close(sock);
	}
/*----------------------------*/
	byte_sent = send(recfd, buffer_1, sizeof(buffer_1), 0);
	if(byte_sent < 0)
		printf("Error sending packet!\n");
/*----------------------------*/
	byte_recv = recv(recfd, buffer, sizeof(buffer), 0);
	if (byte_recv < 0)
		printf("Error recving packet\n");
	printf("Received packet: %s\n", buffer);
}
