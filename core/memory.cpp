
#include "memory.hpp"
#include <cassert>

/* FIXME: not thread-safe */
static uint8_t membuf[65536];
uint8_t Memory::peek(uint32_t addr)
{
	assert(addr >= 0 && addr <= 65535);
	return membuf[addr];
}

void Memory::poke(uint32_t addr, uint8_t val)
{
	assert(addr >= 0 && addr <= 65535);
	membuf[addr] = val;
}

int Memory::peek(lua_State *state)
{
	int args = lua_gettop(state);
	assert(args == 1);
	int addr = luaL_checkint(state, 1);
	uint8_t retval = peek(addr);
	lua_pushnumber(state, retval);
	return 1;
}

int Memory::poke(lua_State *state)
{
	int args = lua_gettop(state);
	assert(args == 2);
	int addr = luaL_checkint(state, 1);
	uint8_t val = luaL_checkint(state, 2);
	poke(addr, val);
	return 0;
}

