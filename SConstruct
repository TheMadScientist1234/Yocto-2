FILES = [
    'core/Main',
    'core/Application'
]

LIBS = [
    'glfw3',
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

env = Environment(
    LIBS=LIBS,
    CXXFLAGS='-std=c++11'
)

O_FILES = []

for file in FILES:
    env.Object(file + '.cpp')
    O_FILES.append(file + '.o')

env.Program('yocto2', O_FILES, LIBS=LIBS)