#include "memory.h"
#include <cstdint>

Memory::Memory(std::size_t size) {
	mem = std::vector<uint8_t>(size);
	addrStart = mem.begin();
}

void Memory::loadState(std::istream& is) {
	int prevPos = is.tellg();
	int streamLength;

	is.seekg(0, std::ios_base::end);
	streamLength = is.tellg() - prevPos;

	if (streamLength > mem.size()-1)
		throw std::exception();

	is.seekg(prevPos);
	is.read(reinterpret_cast<char*>(mem.data()), streamLength);
}