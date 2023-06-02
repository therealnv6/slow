#pragma once
#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace data
{
	class dataset
	{
	public:
		dataset()
		{
		}

		void set(std::string key, std::string value)
		{
			data[key] = value;
		}

		void append(std::string key, std::string value)
		{
			if (!this->has(key))
			{
				this->set(key, value);
			}
			else
			{
				std::string curr = data[key];
				std::string next = curr + value;

				data[key] = next;
			}
		}

		bool del(std::string key)
		{
			if (!this->has(key))
			{
				return false;
			}

			data.erase(data.find(key));
			return true;
		}

		bool has(std::string key)
		{
			return data.contains(key);
		}

		bool increment(const std::string &key)
		{
			auto it = data.find(key);
			std::string &value = it->second;

			try
			{
				int val = std::stoi(value);
				++val;
				value = std::to_string(val);
			} catch (const std::exception &)
			{
				return false;
			}

			return true;
		}

		bool decrement(const std::string &key)
		{
			auto it = data.find(key);
			std::string &value = it->second;

			try
			{
				int val = std::stoi(value);
				--val;
				value = std::to_string(val);
			} catch (const std::exception &)
			{
				return false;
			}

			return true;
		}

		uint size()
		{
			return data.size();
		}

		template<typename T>
		T get(std::string key);

	private:
		std::unordered_map<std::string, std::string> data;
	};
}
