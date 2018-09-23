
#include "memory.hpp"
#include <cassert>
#include <vector>

/* FIXME: not thread-safe */
static std::vector<uint8_t> membuf(65536);

uint8_t Memory::peek(uint32_t addr)
{
	return membuf.at(addr);
}

void Memory::poke(uint32_t addr, uint8_t val)
{
	membuf.at(addr) = val;
}

int Memory::peek(lua_State *state)
{
	int args = lua_gettop(state);
	assert(args == 1);
	int addr = luaL_checkinteger(state, 1);
	uint8_t retval = peek(addr);
	lua_pushnumber(state, retval);
	return 1;
}

int Memory::poke(lua_State *state)
{
	int args = lua_gettop(state);
	assert(args == 2);
	int addr = luaL_checkinteger(state, 1);
	uint8_t val = luaL_checkinteger(state, 2);
	poke(addr, val);
	return 0;
}

