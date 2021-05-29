#pragma once
#include <cstdint>
#include <vector>

class Memory {
	std::vector<uint8_t> mem;

public:
	//Default to 65k of memory
	Memory(uint16_t sz = 65535) {
		mem = std::vector<uint8_t>(sz);
	}
};
