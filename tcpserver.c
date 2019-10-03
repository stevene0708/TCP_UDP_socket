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

int main(int argc, char *argv[]){

	struct sockaddr_in server_addr, client_addr;
	struct timeval fir_send, sec_arrive;	
	int sock, byte_recv, byte_sent, server_addr_length = sizeof(server_addr), client_addr_length = sizeof(client_addr), recfd;
	char buffer[50], buffer_1[50] = "welcome!\0", temp[30], temp_1[30];
	unsigned long diff, temp_sec, temp_usec;
	float data_t;

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

	byte_sent = send(recfd, buffer_1, sizeof(buffer_1), 0);
	gettimeofday(&fir_send, NULL);
	if(byte_sent < 0) printf("Error sending packet!\n");

	sprintf(temp, "%ld", fir_send.tv_sec);
	byte_sent = send(recfd, temp, sizeof(temp), 0);
	if(byte_sent < 0) printf("Error sending packet!\n");
	
	sprintf(temp, "%ld", fir_send.tv_usec);
	byte_sent = send(recfd, temp, sizeof(temp), 0);
	if(byte_sent < 0) printf("Error sending packet!\n");

	byte_recv = recv(recfd, buffer, sizeof(buffer), 0);
	gettimeofday(&sec_arrive, NULL);
	if (byte_recv < 0) printf("Error recving packet\n");
	
	printf("Received packet: %s\n", buffer);

	byte_recv = recv(recfd, temp_1, sizeof(temp_1), 0);
	if (byte_recv < 0) printf("Error recving packet\n");
	temp_sec = atol(temp_1);

	byte_recv = recv(recfd, temp_1, sizeof(temp_1), 0);
	if (byte_recv < 0) printf("Error recving packet\n");
	temp_usec = atol(temp_1);

	diff = 1000000 * (sec_arrive.tv_sec - temp_sec) + sec_arrive.tv_usec - temp_usec;
	data_t = sizeof(buffer) * 8 / diff * 1000000 / pow(2,20);

	printf("Latency: %ld(us)\n", diff);
	printf("Throughput: %.3f(mb/s)\n",data_t);
}
