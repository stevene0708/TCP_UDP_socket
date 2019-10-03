#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define server_portnumber 5555
#define server_address "127.0.0.1"

int main(int argc, char* argv[]){
	struct sockaddr_in address, client_address;
	struct timeval fir_send, sec_recv;
	int sock, byte_sent, byte_recv;
	char buffer[50] = "Hi, i'm 7108056148", buffer_1[50];
	char temp[30], temp_1[30];
	unsigned long diff, temp_sec, temp_usec;
	float data_r;

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock < 0) printf("Error creating socket\n");
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(server_portnumber);
	address.sin_addr.s_addr = inet_addr(server_address);
	
	int address_length = sizeof(address);

	byte_sent = sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, address_length);
	gettimeofday(&fir_send, NULL);
	if (byte_sent < 0) printf("Error sending packet\n");
	
	sprintf(temp, "%ld", fir_send.tv_sec);
	byte_sent = sendto(sock, temp, sizeof(temp), 0, (struct sockaddr*)&address, address_length);
	if (byte_sent < 0) printf("Error sending packet\n");
 
	sprintf(temp, "%ld", fir_send.tv_usec);
	byte_sent = sendto(sock, temp, sizeof(temp), 0, (struct sockaddr*)&address, address_length);
	if (byte_sent < 0) printf("Error sending packet\n");

	byte_recv = recvfrom(sock, buffer_1, sizeof(buffer_1), 0, (struct sockaddr*)&address, &address_length);
	gettimeofday(&sec_recv, NULL);
	if (byte_recv < 0) printf("Error sending packet\n");

	byte_recv = recvfrom(sock, temp_1, sizeof(temp_1), 0, (struct sockaddr*)&address, &address_length);
	if (byte_recv < 0) printf("Error sending packet\n");
	temp_sec = atol(temp_1);

	byte_recv = recvfrom(sock, temp_1, sizeof(temp_1), 0, (struct sockaddr*)&address, &address_length);
	if (byte_recv < 0) printf("Error sending packet\n");
	temp_usec = atol(temp_1);

	diff = 1000000 * (sec_recv.tv_sec - temp_sec) + sec_recv.tv_usec - temp_usec;
	data_r = sizeof(buffer_1) * 8 / diff * 1000000 / pow(2, 20);
	printf("packet content: %s", buffer_1);
	printf("Latency: %ld(us)\n", diff);
	printf("Throughput: %.3f(mb/s)\n", data_r);
	close(sock);
	return 0;
}
