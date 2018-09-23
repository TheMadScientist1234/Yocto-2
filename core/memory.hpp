
#include "lua.hpp"
#include <cstdint>

namespace Memory {
	uint8_t peek(uint32_t addr);
	int peek(lua_State *state);
	void poke(uint32_t addr, uint8_t val);
	int poke(lua_State *state);
};
