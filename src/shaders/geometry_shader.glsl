#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

struct Model {
    vec3 color;
    uint padding;
};

layout(std140) uniform modelData {
    Model[4096] models;
};

uniform mat4 camera;
uniform mat4 chunkOffset;

out vec3 color;

void main() {

    uint data = uint(gl_in[0].gl_Position.w);

    uint model_id = data & 0xfff;

    uint face_data = (data>>12) & 0x7;
    // 17 bits left over currently

    // dont need bit mask because face_data only has 3 set bits
    float plane_offset = (face_data>>2) - 0.5;
    uint plane_index = face_data & 0x3;

    mat4 planes[3] = mat4[](
        mat4( // side plane
            vec4(0.0, 0.5, -.5, 1),
            vec4(0.0, 0.5, 0.5, 1),
            vec4(0.0, -.5, -.5, 1),
            vec4(0.0, -.5, 0.5, 1)
        ),
         mat4( // horizontal plane
            vec4(0.5, 0.0, -.5, 1),
            vec4(0.5, 0.0, 0.5, 1),
            vec4(-.5, 0.0, -.5, 1),
            vec4(-.5, 0.0, 0.5, 1)
        ),
        mat4( // front plane
            vec4(-.5, 0.5, 0.0, 1),
            vec4(0.5, 0.5, 0.0, 1),
            vec4(-.5, -.5, 0.0, 1),
            vec4(0.5, -.5, 0.0, 1)
        )
    );

    mat4 plane = planes[plane_index];
    plane[0][plane_index] = plane_offset;
    plane[1][plane_index] = plane_offset;
    plane[2][plane_index] = plane_offset;
    plane[3][plane_index] = plane_offset;

    color = models[model_id].color;

    mat4 thingy = camera * chunkOffset;

    vec4 in_pos = vec4(gl_in[0].gl_Position.xyz,1);

    gl_Position = thingy * (plane[0] + in_pos);
    EmitVertex();

    gl_Position = thingy * (plane[1] + in_pos);
    EmitVertex();

    gl_Position = thingy * (plane[2] + in_pos);
    EmitVertex();

    gl_Position = thingy * (plane[3] + in_pos);
    EmitVertex();

    EndPrimitive();
}