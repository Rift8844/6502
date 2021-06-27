#include "memory.h"
#include <cstdint>

Memory::Memory(std::size_t sz) : size{sz} {
	mem = std::vector<uint8_t>(sz);
	addrStart = mem.begin();
}

void Memory::loadState(std::istream& is, int streamOff, int memOff) {
	int prevPos = is.tellg();

	is.seekg(0, std::ios_base::end);
	std::size_t streamLength = is.tellg() - prevPos;

	if (streamLength > mem.size()-1)
		throw std::exception();

	is.seekg(prevPos+streamOff);

	is.read(reinterpret_cast<char*>(mem.data()+memOff), std::max(size, streamLength));
}