#include <stdexcept>
#include <iostream>

#include "Application.hpp"

#include <GL/gl.h>

#include <lua5.2/lua.hpp>

static void print_error(lua_State* state) {
  // The error message is on top of the stack.
  // Fetch it, print it and then pop it off the stack.
  const char* message = lua_tostring(state, -1);
  puts(message);
  lua_pop(state, 1);
}

static void execute(const char* filename)
{
  lua_State *state = luaL_newstate();

  // Make standard libraries available in the Lua object
  luaL_openlibs(state);

  int result;

  // Load the program; this supports both source code and bytecode files.
  result = luaL_loadfile(state, filename);

  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }

  // Finally, execute the program by calling into it.
  // Change the arguments if you're not running vanilla Lua code.

  result = lua_pcall(state, 0, LUA_MULTRET, 0);

  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }
}

class TestApp : public Application
{
private:
	char inputBuffer[10000];
public:
    void Create()
    {
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);
	std::string s;
        Application::Create();
	luaL_dostring(state, "test");
	while(1) {
		std::cout << "> ";
		std::cout.flush();
		std::cin >> s;
		std::cout << "Entered: " << s << std::endl;
		luaL_dostring(state, s.c_str());
	}
	lua_close(state);
    }

    void Draw()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        Application::Draw();
    }

    void Dispose()
    {
        Application::Dispose();
    }
};

int main()
{
    TestApp app;

    app.Create();

    while(!app.GetShouldClose())
    {
        app.Draw();
    }

    app.Dispose();

    return 0;
}
