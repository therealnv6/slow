#include <dataset.hpp>
#include <stdint.h>

namespace data
{
	template<>
	std::string dataset::get<std::string>(std::string key)
	{
		return data[key];
	}

	template<>
	int dataset::get<int>(std::string key)
	{
		return std::stoi(data[key]);
	}

	template<>
	uint8_t dataset::get<uint8_t>(std::string key)
	{
		return std::stoi(data[key]);
	}

	template<>
	uint16_t dataset::get<uint16_t>(std::string key)
	{
		return std::stoi(data[key]);
	}
}
