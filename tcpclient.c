#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define server_portnumber 5555
#define server_address "127.0.0.1"

int main(int argc, char *argv[]){
	struct sockaddr_in server_addr;
	struct timeval fir_arrive, sec_send;
	int sock, byte_sent, byte_recv, server_addr_length = sizeof(server_addr);
	char buffer[50] = "Hi I'm 7108056148\0", buffer_1[50], temp[30], temp_1[30];	
	unsigned long diff, temp_sec, temp_usec;
	float data_t;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Error creating socket!\n");

	bzero(&server_addr, server_addr_length);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_portnumber);
	server_addr.sin_addr.s_addr = inet_addr(server_address);

	if (connect(sock, (struct sockaddr *)&server_addr, server_addr_length) == -1){
		printf("connect failed!\n");
		close(sock);
		return 0;
	}

	byte_recv = recv(sock, buffer_1, sizeof(buffer_1), 0);
	gettimeofday(&fir_arrive, NULL);
        if (byte_recv < 0) printf("Error recving packet\n");
	printf("packet content: %s\n", buffer_1);

	byte_recv = recv(sock, temp, sizeof(temp), 0);
	if (byte_recv < 0) printf("Error recving packet\n");
	temp_sec = atol(temp);

	byte_recv = recv(sock, temp, sizeof(temp), 0);
	if (byte_recv < 0) printf("Error recving packet\n");
	temp_usec = atol(temp);

	diff = 1000000 * (fir_arrive.tv_sec - temp_sec) + fir_arrive.tv_usec - temp_usec;
	data_t = sizeof(buffer_1) * 8 / diff * 1000000 / pow(2, 20);
	printf("Latency: %ld(us)\n", diff);
	printf("Throughput: %.3f(mb/s)\n", data_t);

	byte_sent = send(sock, buffer, sizeof(buffer), 0);
	gettimeofday(&sec_send, NULL);
	if (byte_sent < 0) printf("Error sending packet!\n");

	sprintf(temp_1, "%ld", sec_send.tv_sec);
	byte_sent = send(sock, temp_1, sizeof(temp_1), 0);
	if (byte_sent < 0) printf("Error sending packet!\n");

	sprintf(temp_1, "%ld", sec_send.tv_usec);
	byte_sent = send(sock, temp_1, sizeof(temp_1), 0);
	if (byte_sent < 0) printf("Error sending packet!\n");

	close(sock);
	return 0;
}
	
		
		
