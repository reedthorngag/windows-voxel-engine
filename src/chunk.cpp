

#include "generation/generator.hpp"
#include "chunk.hpp"

extern Global global;

inline bool Chunk::subChunkSolid(glm::ivec3 pos) {
    return (long long)this->subChunks[pos.x][pos.y][pos.z] & (1LL<<63);
}

inline block Chunk::getBlock(glm::ivec3 pos) {
    SubChunk subChunk = this->subChunks[pos.x>>6][pos.y>>6][pos.z>>6];

    if ((long long)subChunk & (1LL<<63))
        return (block)((long long)subChunk & 0xffff);
    
    return subChunk[pos.x&0x3f][pos.y&0x3f][pos.z&0x3f];
}

void Chunk::generateMesh() {
    
}

Chunk::Chunk(glm::ivec3* pos) {
    this->pos = pos;
    global.generator.generateChunk(this);
}

Chunk::~Chunk() {
    for (int x = 0; x < CHUNK_SUB_CHUNKS; x++) {
        for (int y = 0; y < CHUNK_SUB_CHUNKS; y++) {
            for (int z = 0; z < CHUNK_SUB_CHUNKS; z++) {
                SubChunk subChunk = this->subChunks[x][y][z];
                if (!((long long)subChunk & (1LL<<63)))
                    delete subChunk;
            }
        }
    }
}

