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
			registers.emplace("app", &parser::app);
			registers.emplace("del", &parser::del);
			registers.emplace("len", &parser::len);
			registers.emplace("inc", &parser::inc);
			registers.emplace("dec", &parser::dec);
			registers.emplace("exists", &parser::exists);
		}

		std::string execute(std::string command, data::key key)
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

		std::string get(data::key key)
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

		std::string set(data::key key)
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

		std::string app(data::key key)
		{
			size_t delimIndex = key.find(':');
			if (delimIndex != std::string::npos && delimIndex < key.size() - 1)
			{
				std::string value = key.substr(delimIndex + 1);
				key = key.substr(0, delimIndex);
				data.append(key, value);
				return "OK";
			}
			else
			{
				return std::format("[ES3] No command provided, key={}", key);
			}
		}

		std::string del(data::key key)
		{
			return data.has(key) && data.del(key) ? "OK" : "N/A";
		}

		std::string inc(data::key key)
		{
			return data.has(key) && data.increment(key) ? "OK" : "N/A";
		}

		std::string dec(data::key key)
		{
			return data.has(key) && data.decrement(key) ? "OK" : "N/A";
		}

		std::string exists(data::key key)
		{
			return std::to_string(data.has(key));
		}

		std::string len(data::key key)
		{
			return std::to_string(data.size());
		}

	private:
		std::unordered_map<std::string, function> registers;

		server::tcp_server &server;
		data::dataset &data;
	};
}
