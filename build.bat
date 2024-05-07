@echo off

cls
g++ -Wall -g -W -Werror -Wno-unused-parameter -Wno-unused-variable ^
    -I C:/lib/glm ^
    -I C:/lib/glew/include ^
    -I C:/lib/glfw/include ^
    -L C:\lib\glew\lib\Release\x64 ^
    -L C:\lib\glfw\lib-mingw-w64 ^
    src/main.cpp ^
    -lopengl32 -lglew32 -lglfw3 -lgdi32 ^
    -o bin/output.exe || exit 1
