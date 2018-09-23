FILES = [
    'core/Main',
    'core/Application',
    'core/memory'
]

LIBS = [
    'lua5.2',
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
    'dl'
]

O_FILES = []

for file in FILES:
    Object(file + '.cpp', CXXFLAGS='-std=c++11')
    O_FILES.append(file + '.o')

Program('yocto2', O_FILES, LIBS=LIBS, CXXFLAGS='-std=c++11')
