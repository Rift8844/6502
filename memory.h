#include <cstdint>
#include <vector>

#pragma once

/*We can use a memory class to emulate the address bus, and
add peripheral support later. Using an address class will easily
allow us to switch from memory unsafe "std::vector operator[]"" to
memory safe "std::vector get()"*/
class Memory {
	//Standard memory space for now
	std::vector<uint8_t> mem;
	std::vector<uint8_t>::iterator addrStart;

public:
	Memory(std::size_t size);

	//Leave as uint8_t for now
	uint8_t& operator[](uint16_t idx) { return addrStart[idx]; }
	uint8_t const operator[](uint16_t idx) const { return addrStart[idx]; }


	//Get in Little Endian format
	uint8_t& getLE(uint16_t addr) { return (val << 8)|(val >> 8); }
	uint8_t const getLE(uint16_t addr) const { return (val << 8)|(val >> 8); }
};