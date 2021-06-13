#include "memory.h"
#include <cstdint>

Memory::Memory(std::size_t size) {
	mem = std::vector<uint8_t>(size);
	addrStart = mem.begin();
}
