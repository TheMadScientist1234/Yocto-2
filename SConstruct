FILES = [
    'main',
    'window/window'
]

LIBS = [
    'X11',
    'GL',
    'GLEW',
    'GLX'
]

O_FILES = []

for file in FILES:
    Object(file + '.cpp')
    O_FILES.append(file + '.o')

Program('yocto2', O_FILES, LIBS=LIBS)