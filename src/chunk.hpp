#include <GL/glew.h>
#include <glm/glm.hpp>

#include "globals.hpp"

#ifndef _CHUNK
#define _CHUNK

typedef block (*SubChunk)[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE];
// #pragma pack(1)
// struct SubChunk {
//     block (*blocks)[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE];
// };

#pragma pack(1)
struct face {
    float a;
    float b;
};

class Chunk {
    private:

    public:
        glm::ivec3* pos;

        // I am doing something you should never do by using the top bit of the pointer to indicate if
        // its a solid sub chunk or not, in theory this would break if the pointer used the highest bit
        // but that *shouldnt* ever happen in practice
        SubChunk subChunks[CHUNK_SUB_CHUNKS][CHUNK_SUB_CHUNKS][CHUNK_SUB_CHUNKS] = {};

        GLuint VAO;
        GLuint VBO;

        int faces;

        inline bool subChunkSolid(glm::ivec3 pos);
        inline block getBlock(glm::ivec3 pos);
        inline block getBlock(int x, int y, int z, int x1, int y1, int z1);

        void generateMesh();

        Chunk(glm::ivec3* pos);
        ~Chunk();
};

#endif

