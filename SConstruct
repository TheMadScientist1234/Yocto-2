FILES = [
    'core/Main',
    'core/Application',
    'core/memory',

    'graphics/Texture',
    'graphics/FontRenderer'
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
    'SOIL'
]

O_FILES = []

for file in FILES:
    Object(file + '.cpp', CXXFLAGS='-std=c++11 -DLUA_USE_LINUX -DLUA_COMPAT_5_2', CPPPATH=[ '.' ])
    O_FILES.append(file + '.o')

O_FILES.append('lua/liblua.a')

Command("lua/liblua.a", "", "cd lua && make")
Program('yocto2', O_FILES, LIBS=LIBS, CXXFLAGS='-std=c++11', LIBPATH = [ 'lua' ])
