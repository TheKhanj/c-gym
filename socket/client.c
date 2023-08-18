#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void printBinary(int num) {
    for (int i = sizeof(uint16_t) * 8 - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
}

int main() {
	// Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return 1;
	}

	// Define server address
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);									// Server port
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP (localhost)

	printBinary(1);
	printf("\n");
	printBinary(htons(1));
	printf("\n");
	// Connect to the server
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
			-1) {
		perror("connect");
		return 1;
	}

	// Send data to server
	char message[] = "Hello, server!";
	send(sockfd, message, strlen(message), 0);

	// Receive data from server
	char buffer[1024];
	ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
	if (bytes_received <= 0) {
		perror("recv");
		return 1;
	}

	buffer[bytes_received] = '\0';
	printf("Received from server: %s\n", buffer);

	// Close the socket
	close(sockfd);

	return 0;
}
