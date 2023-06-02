#pragma once

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

const int BUFFER_SIZE = 1024;

namespace server
{

	class tcp_server
	{
	public:
		tcp_server(int port)
		{
			server_sock = socket(AF_INET, SOCK_STREAM, 0);
			if (server_sock == -1)
			{
				throw std::runtime_error("error creating socket");
			}

			// Prepare the server address
			sockaddr_in address {
				.sin_family = AF_INET,
				.sin_port = htons(port),
			};

			address.sin_addr.s_addr = INADDR_ANY;

			// Bind the socket to the server address
			if (bind(server_sock, (struct sockaddr *) &address, sizeof(address)) == -1)
			{
				throw std::runtime_error("error binding socket (is there already a server running on this port?)");
			}

			// Listen for incoming connections
			if (listen(server_sock, 5) == -1)
			{
				close(server_sock);
				throw std::runtime_error("error listening for connections");
			}
		}

		~tcp_server()
		{
			close(server_sock);
		}

		void accept_client()
		{
			sockaddr_in address;
			socklen_t address_length = sizeof(address);

			int clientSocket = accept(server_sock, (struct sockaddr *) &address, &address_length);

			if (clientSocket == -1)
			{
				throw std::runtime_error("error accepting client connection");
			}

			// Receive client request
			memset(buffer, 0, sizeof(buffer));
			ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

			if (bytesRead == -1)
			{
				throw std::runtime_error("error receiving data from client");
			}

			client_socks.push_back(clientSocket);
		}

		void close_clients()
		{
			for (int socket : client_socks)
			{
				close(socket);
			}

			client_socks.clear();
		}

		void send_to_client(std::string response)
		{
			auto cstr = response.c_str();
			int length = response.size();

			for (int socket : client_socks)
			{
				if (send(socket, response.c_str(), response.size(), 0) == -1)
				{
					throw std::runtime_error("error sending response to client");
				}
			}
		}

		char *get_buffer()
		{
			return buffer;
		}

		std::string get_buffer_as_str()
		{
			return buffer;
		}

	private:
		char buffer[BUFFER_SIZE];
		int server_sock;
		std::vector<int> client_socks;
	};
}
