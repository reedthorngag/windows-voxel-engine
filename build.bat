@echo off

cls
g++ -Wall -g -W -Werror -Wno-unused-parameter -Wno-unused-variable ^
    -I C:/lib ^
    -I C:/lib/glew/include ^
    -I C:/lib/glfw/include ^
    -I ./include ^
    -L C:\lib\glew\lib\Release\x64 ^
    -L C:\lib\glfw\lib-mingw-w64 ^
    src/*.cpp ^
    -lopengl32 -lglew32 -lglfw3 -lgdi32 ^
    -o bin/output.exe || exit 1
