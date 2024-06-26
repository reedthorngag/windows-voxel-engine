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

class Chunk {
    private:

    public:
        glm::ivec3* pos;

        // I am doing something you should never do by using the top bit to indicate if
        // its a solid sub chunk or not, in theory this would break if the pointer used the highest bit
        // but that *shouldnt* ever happen in practice
        SubChunk subChunks[CHUNK_SUB_CHUNKS][CHUNK_SUB_CHUNKS][CHUNK_SUB_CHUNKS] = {};

        inline bool subChunkSolid(glm::ivec3 pos);
        inline block getBlock(glm::ivec3 pos);

        Chunk(glm::ivec3* pos);
        ~Chunk();
};

#endif

