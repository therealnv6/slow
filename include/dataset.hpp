#pragma once
#include <iostream>
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

		bool has(std::string key)
		{
			return data.contains(key);
		}

		template<typename T>
		T get(std::string key);

	private:
		std::unordered_map<std::string, std::string> data;
	};
}
