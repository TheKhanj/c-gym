#include<errno.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define KHANJ KHANJ

int sockfd = -1;
void close_socket(int sig) {
	printf("SIGINT\n");

	if (sockfd != -1) {
		printf("closing socket %d\n", sockfd);
		close(sockfd);
		exit(0);
	}
}

int main() {
	perror("hello");
	perror("hello");
	perror("hello");
	perror("hello");
	struct sigaction action;
	action.sa_handler = close_socket;
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) == -1) {
		perror("sigaction");
	}

	// Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		return 1;
	}

	int reuse = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	// Define server address
	struct sockaddr_storage fo;
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345); // Port number
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
			-1) {
		perror("bind");
		close_socket(0);
		return 1;
	}

	// Listen for incoming connections
	if (listen(sockfd, 5) == -1) {
		perror("listen");
		close_socket(0);
		return 1;
	}

	printf("Server is listening...\n");

	// Accept and handle connections
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	while (1) {
		int client_fd =
				accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_fd == -1) {
			perror("accept");
			continue;
		}

		char buffer[1024];
		ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
		if (bytes_received <= 0) {
			perror("recv");
			close(client_fd);
			continue;
		}

		printf("Received: %s\n", buffer);
		sleep(1);
		send(client_fd, buffer, bytes_received, 0);
		fflush(stdout);

		close(client_fd);
	}

	close_socket(0);

	return 0;
}
