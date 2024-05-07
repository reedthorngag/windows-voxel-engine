#version 460 core
layout (location = 0) in uint pos;

void main() {

    gl_Position = vec4((pos & 0xff)*0.1,((pos>>8) & 0xff)*0.1,((pos>>16) & 0xff)*0.1, 1.0);
}