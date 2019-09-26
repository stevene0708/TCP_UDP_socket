#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define server_portnumber 5555
#define server_address "127.0.0.1"

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr;
	int sock, byte_sent, byte_recv, server_addr_length = sizeof(server_addr);
	char buffer[] = "Hi I'm 7108056148\0", buffer_1[10];
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Erroer creating socket!\n");
	bzero(&server_addr, server_addr_length);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_portnumber);
	server_addr.sin_addr.s_addr = inet_addr(server_address);

	if (connect(sock, (struct sockaddr *)&server_addr, server_addr_length) == -1){
		printf("connect failed!");
		close(sock);
	}
	
	byte_recv = recv(sock, buffer_1, sizeof(buffer_1), 0);
        if (byte_recv < 0) 
		printf("Error recving packet\n");
	printf("packet content: %s\n", buffer_1);

	byte_sent = send(sock, buffer, sizeof(buffer), 0);
	if (byte_sent < 0)
		printf("Error sending packet!\n");

	close(sock);
	return 0;
}
	
		
		
