#include <algorithm>
#include <parser.hpp>
#include <server.hpp>
#include <spdlog/spdlog.h>

void rtrim(std::string &s)
{
	s.erase(std::find_if_not(s.rbegin(), s.rend(), [](unsigned char ch) {
		return std::isspace(ch);
	}).base(),
		s.end());
}

int main()
{
	try
	{
		server::tcp_server server(8080);
		data::dataset data;

		parse::parser parser(server, data);

		spdlog::info("opening server on port 8080");

		while (true)
		{
			server.accept_client();

			std::string buffer = server.get_buffer();

			std::string command = buffer.substr(0, buffer.find(' '));
			std::string key = buffer.substr(buffer.find(' ') + 1, buffer.size() - 1);

			rtrim(key);

			std::string response = parser.execute(command, key);

			server.send_to_client(response);
			server.close_clients();
		}
	} catch (std::runtime_error &e)
	{
		spdlog::error("ran into an issue: {}", e.what());
	}

	return 0;
}
