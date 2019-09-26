#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define server_portnumber 5555
#define server_address "127.0.0.1"

int main(int argc, char* argv[]){
	struct sockaddr_in address, client_address;
	int sock, byte_sent, byte_recv;
	char buffer[] = "Hi, i'm 7108056148", buffer_1[50];

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock < 0) printf("Error creating socket\n");
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(server_portnumber);
	address.sin_addr.s_addr = inet_addr(server_address);
	
	int address_length = sizeof(address);

	byte_sent = sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, address_length);
	if (byte_sent < 0) printf("Error sending packet\n");

	byte_recv = recvfrom(sock, buffer_1, sizeof(buffer), 0, (struct sockaddr*)&address, &address_length);
	if (byte_recv < 0) printf("Error sending packet\n");
	printf("packet content: %s\n", buffer_1);
	close(sock);
	return 0;
}
