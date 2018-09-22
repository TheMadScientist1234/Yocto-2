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

O_FILES = []

for file in FILES:
    Object(file + '.cpp')
    O_FILES.append(file + '.o')

Program('yocto2', O_FILES, LIBS=LIBS)