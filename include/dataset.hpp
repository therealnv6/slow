#pragma once
#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace data
{
	typedef std::string key;
	typedef std::string value;

	class dataset
	{
	public:
		dataset()
		{
		}

		void set(const data::key &key, const data::value &value)
		{
			data[key] = value;
		}

		void append(const data::key &key, const data::value &value)
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

		bool del(const data::key &key)
		{
			if (!this->has(key))
			{
				return false;
			}

			data.erase(data.find(key));
			return true;
		}

		[[nodiscard("must be used, only checks if data container contains the key")]] bool has(data::key key)
		{
			return data.contains(key);
		}

		bool increment(const data::key &key)
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

		bool decrement(const data::key &key)
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

		[[nodiscard("must be used, only retrieves size")]] uint size()
		{
			return data.size();
		}

		template<typename T>
		[[nodiscard("must be used, only returns the value retrieved from the data container")]] T get(const std::string &key);

	private:
		std::unordered_map<data::key, data::value> data;
	};
}
