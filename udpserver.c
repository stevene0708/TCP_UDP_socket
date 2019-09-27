#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnumber 5555

int main(int argc, char* argv[]){
	struct sockaddr_in address;// , client_address;
	int sock, byte_recv, byte_sent, client_address_length;
	char buffer[50], buffer_1[] = "Welcome!\n";

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) printf("Error creating socket\n");
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(portnumber);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr*)&address, sizeof(address)) == -1){
		printf("Error binding\n");
		close(sock);
	}

	int address_length = sizeof(address);
	
	while(1){
		byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, &address_length);
		if (byte_recv < 0) printf("Error recving packet\n");
		printf("data: %s\n", buffer);

		byte_sent = sendto(sock, buffer_1, sizeof(buffer_1), 0, (struct sockaddr*)&address, address_length);
               


	}

	return 0;
}
