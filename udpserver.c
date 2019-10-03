#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnumber 5555

int main(int argc, char* argv[]){
	struct sockaddr_in address;// , client_address;
	struct timeval fir_recv, sec_send;
	int sock, byte_recv, byte_sent, client_address_length;
	char buffer[50], buffer_1[50] = "Welcome!\n";
	char temp[30], temp_1[30];
	float data_r;
	unsigned long diff, temp_sec, temp_usec;

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
		gettimeofday(&fir_recv, NULL);	
		if (byte_recv < 0) printf("Error recving packet\n");

		byte_recv = recvfrom(sock, temp, sizeof(temp), 0, (struct sockaddr*)&address, &address_length);
		if (byte_recv < 0) printf("Error recving packet\n");
		temp_sec = atol(temp);

		byte_recv = recvfrom(sock, temp, sizeof(temp), 0, (struct sockaddr*)&address, &address_length);
		if (byte_recv < 0) printf("Error recving packet\n");
		temp_usec = atol(temp);

		diff = 1000000 * (fir_recv.tv_sec - temp_sec) + fir_recv.tv_usec - temp_usec;
		data_r = sizeof(buffer) * 8 / diff * 1000000 / pow(2, 20);
		printf("data: %s\n", buffer);
		printf("Latency: %ld(us)\n", diff);
		printf("Throughtput: %.3f(mb/s)\n", data_r);

		byte_sent = sendto(sock, buffer_1, sizeof(buffer_1), 0, (struct sockaddr*)&address, address_length);
		gettimeofday(&sec_send, NULL);

		sprintf(temp_1, "%ld", sec_send.tv_sec);
		byte_sent = sendto(sock, temp_1, sizeof(temp_1), 0, (struct sockaddr*)&address, address_length);
		sprintf(temp_1, "%ld", sec_send.tv_usec);
		byte_sent = sendto(sock, temp_1, sizeof(temp_1), 0, (struct sockaddr*)&address, address_length);
	}

	return 0;
}
