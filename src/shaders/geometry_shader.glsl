#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 16) out;

struct Model {
    vec3 color;
    uint padding;
};

layout(std140) uniform modelData {
    Model[] models;
};

//uniform mat4 camera;
//uniform mat4 chunkOffset;

out vec3 color;

void main() {
    color = models[1].color;

    gl_Position = vec4(0.5,0,0,1);
    EmitVertex();

    gl_Position = vec4(0.5,0.5,0,1);
    EmitVertex();

    gl_Position = vec4(0,0,0,1);
    EmitVertex();

    EndPrimitive();
}