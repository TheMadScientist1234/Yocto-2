FILES = [
    'core/Main',
    'core/Application',
    'core/memory',
    'core/Console',

    'graphics/Texture',
    'graphics/Font'
]

LIBS = [
    'glfw',
    'X11',
    'Xi',
    'Xxf86vm',
    'Xcursor',
    'Xinerama',
    'GL',
    'GLEW',
    'pthread',
    'rt',
    'dl',
    'SOIL',
    'freetype'
]


O_FILES = []


debug = ARGUMENTS.get('debug', 0)

for file in FILES:
    if int(debug):
        Object(file + '.cpp', CXXFLAGS='-std=c++11 -DLUA_USE_LINUX -DLUA_COMPAT_5_2 -g', CPPPATH=[ '.', 'freetype2/include' ])
    else:
        Object(file + '.cpp', CXXFLAGS='-std=c++11 -DLUA_USE_LINUX -DLUA_COMPAT_5_2', CPPPATH=[ '.', 'freetype2/include' ])
    O_FILES.append(file + '.o')

O_FILES.append('lua/liblua.a')

Command("lua/liblua.a", "", "cd lua && make")
Command("freetype2/objs/libfreetype.a", "", "cd freetype2 && jam")
Program('yocto2', O_FILES, LIBS=LIBS, CXXFLAGS='-std=c++11 -g', LIBPATH = [ 'lua', 'freetype2/objs' ])
