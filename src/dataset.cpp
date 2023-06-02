#include <dataset.hpp>
#include <stdint.h>

namespace data
{
	template<>
	std::string dataset::get<std::string>(const data::key &key)
	{
		return data[key];
	}

	template<>
	int dataset::get<int>(const data::key &key)
	{
		return std::stoi(data[key]);
	}

	template<>
	uint8_t dataset::get<uint8_t>(const data::key &key)
	{
		return std::stoi(data[key]);
	}

	template<>
	uint16_t dataset::get<uint16_t>(const data::key &key)
	{
		return std::stoi(data[key]);
	}
}
