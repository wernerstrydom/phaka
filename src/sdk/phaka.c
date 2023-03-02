// Licensed to Werner Strydom under one or more agreements.
// Werner Strydom licenses this file to you under the MIT license.

//
// Created by Werner Strydom on 3/1/23.
//

#include "phaka.h"
#include "private-platform.h"
#include "private-version.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

/*********************************************************************
 * System Information
 *********************************************************************/
const char* phaka_version()
{
	return PHAKA_VERSION;
}

const char* phaka_system_name(void)
{
	return PHAKA_SYSTEM;
}

const char* phaka_system_arch(void)
{
	return PHAKA_ARCH;
}

/*********************************************************************
 * Error Handling
 *********************************************************************/
const char* phaka_error_message(phaka_error_t* error)
{
	return error->message;
}

int phaka_error_code(phaka_error_t* error)
{
	return error->code;
}

void phaka_error_free(phaka_error_t* error)
{
	free(error->message);
	free(error);
}

phaka_error_t* phaka_error_new(int code, const char* message)
{
	phaka_error_t* error = malloc(sizeof(phaka_error_t));
	error->code = code;
	error->message = malloc(strlen(message) + 1);
	strcpy(error->message, message);
	return error;
}

/*********************************************************************
 * Server
 *********************************************************************/
struct phaka_server_t {
	int port;
};

phaka_server_t* phaka_server_new(int port)
{
	phaka_server_t* server = malloc(sizeof(phaka_server_t));
	server->port = port;
	return server;
}


void phaka_server_free(phaka_server_t* server)
{
	free(server);
}
void phaka_server_run(phaka_server_t* server, phaka_error_t** error)
{
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	char buffer[8192];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
	{
		*error = phaka_error_new(1, "Could not create socket");
		return;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(buffer, 0, sizeof(buffer));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(server->port);

	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		*error = phaka_error_new(2, "Could not bind socket");
		return;
	}

	const int max_connections = 10;
	if(listen(listenfd, max_connections) == -1)
	{
		*error = phaka_error_new(3, "Could not listen on socket");
		return;
	}

	for(;;)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);

		ssize_t rc;
		int n = 0;
		connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
		if(connfd == -1)
		{
			*error = phaka_error_new(4, "Could not accept connection");
			return;
		}

		// print ip address
		inet_ntop(AF_INET, &client_addr.sin_addr, buffer, sizeof(buffer));
		printf("Client IP: %s Port: %d\n", buffer, ntohs(client_addr.sin_port));

		while( (n = recv(connfd, buffer, sizeof(buffer), 0)) > 0)
		{
			printf("%s", buffer);
			if (buffer[n - 1] == '\n' && buffer[n - 2] == '\r' && buffer[n - 3] == '\n' && buffer[n - 4] == '\r')
			{
				break;
			}
			memset(buffer, 0, sizeof(buffer));
		}
		if (n < 0)
		{
			*error = phaka_error_new(5, "Could not read from socket");
			return;
		}

		memset(buffer, 0, sizeof(buffer));
		snprintf(buffer, sizeof(buffer), "HTTP/1.0 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!");
		if((rc = send(connfd, buffer, strlen(buffer), 0)) < 0)
		{
			// TODO Convert rc to proper error code
			*error = phaka_error_new(6, "Could not write to socket");
			return;
		}
		close(connfd);
	}
	close(listenfd);
}
