#include "memory.h"
#include <cstdint>

Memory::Memory(std::size_t sz) : size{sz} {
	mem = std::vector<uint8_t>(sz);
	addrStart = mem.begin();
}

void Memory::loadState(std::istream& is, int memOff, int streamOff) {

	is.seekg(0, is.end);
	std::size_t streamLength = is.tellg();
	is.seekg(streamOff);

	/*if (streamLength > mem.size()-1)
		throw std::exception();*/

	is.read(reinterpret_cast<char*>(mem.data()+memOff), std::min(size - memOff, streamLength));
}