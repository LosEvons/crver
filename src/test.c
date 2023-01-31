#include "server.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void launch(struct Server *server){
	char buffer[30000];
	char *hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, World!</h1></body></html>";
	int addressLength = sizeof(server->address);
	int newSocket;

	while (1)
	{
		printf("===== WAITING FOR CONNECTION =====\n");
		newSocket = accept(server->socket,
				(struct sockaddr *)&server->address,
				(socklen_t *)&addressLength);
		read(newSocket, buffer, sizeof(buffer));
		printf("%s\n", buffer);

		write(newSocket, hello, strlen(hello));
		close(newSocket);
	}	
}



int main(){
	struct Server server = server_constructor(AF_INET, SOCK_STREAM,
					0, INADDR_ANY, 8989, 10, launch);
	server.launch(&server);
}