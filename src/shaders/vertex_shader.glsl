#version 460 core
layout (location = 0) in float pos;

void main() {

    // pos is 10 bits for x and y and 12 for z

    //gl_Position = vec4((uint(pos[0]) & 0x3ff),((uint(pos[0])>>10) & 0x3ff)+mod,((uint(pos[0])>>20) & 0xfff), pos[1]);
    gl_Position = vec4(pos,pos,0,0x2000);
}