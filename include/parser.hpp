#pragma once
#include <dataset.hpp>
#include <format>
#include <server.hpp>
#include <string>
#include <unordered_map>

namespace parse
{

	class parser
	{
		typedef std::string (parser::*function)(std::string);

	public:
		parser(server::tcp_server &server, data::dataset &data)
			: server(server)
			, data(data)
		{
			registers.emplace("get", &parser::get);
			registers.emplace("set", &parser::set);
		}

		std::string execute(std::string command, std::string key)
		{
			if (key.empty())
			{
				return "[ES1] No key provided";
			}

			auto call = registers.find(command);

			if (call == registers.end())
			{
				return "[ES5] Unknown command";
			}

			function callback = registers[command];
			auto result = (this->*callback)(key);

			return result;
		}

		std::string get(std::string key)
		{
			if (data.has(key))
			{
				return data.get<std::string>(key);
			}
			else
			{
				return std::format("[ES2] Key not in database: {}", key);
			}
		}

		std::string set(std::string key)
		{
			size_t delimIndex = key.find(':');
			if (delimIndex != std::string::npos && delimIndex < key.size() - 1)
			{
				std::string value = key.substr(delimIndex + 1);
				key = key.substr(0, delimIndex);
				data.set(key, value);
				return "OK";
			}
			else
			{
				return std::format("[ES3] No command provided, key={}", key);
			}
		}

	private:
		std::unordered_map<std::string, function> registers;

		server::tcp_server &server;
		data::dataset &data;
	};
}
