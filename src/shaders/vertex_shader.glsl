#version 460 core
layout (location = 0) in float pos;
layout (location = 1) in float data;

void main() {

    // pos is 10 bits for x and y and 12 for z

    gl_Position = vec4(
        uint(pos) & 0x3ff,
        (uint(pos)>>10) & 0x3ff,
        (uint(pos)>>20) & 0x3ff,
        data);
}