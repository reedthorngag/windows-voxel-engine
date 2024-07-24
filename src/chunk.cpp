#include <vector>
#include <stdio.h>

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
    
    return subChunk[pos.x&0x1f][pos.y&0x1f][pos.z&0x1f];
}

inline block Chunk::getBlock(int x, int y, int z, int x1, int y1, int z1) {
    SubChunk subChunk = this->subChunks[x][y][z];
    
    if ((long long)subChunk & (1LL<<63))
        return (block)((long long)subChunk & 0xffff);

    return subChunk[x1][y1][z1];
}

inline void addFace(std::vector<face>* faces, int x, int y, int z, short blockId, char faceId, bool side) {
    faces->push_back(face{
                        (float)((x << 22) | ((y & 0x3ff) << 12) | ((z & 0x3ff) << 2)),
                        (float)((blockId << 20) | ((faceId & 0x3) << 18) | (side << 17))
                    });
}

void Chunk::generateMesh() {
    std::vector<face>* faces = new std::vector<face>;

    for (short x = 0; x < CHUNK_SUB_CHUNKS; x++) {
        for (short y = 0; y < CHUNK_SUB_CHUNKS; y++) {
            for (short z = 0; z < CHUNK_SUB_CHUNKS; z++) {

                SubChunk subChunk = this->subChunks[x][y][z];

                for (short x1 = 0; x1 < SUB_CHUNK_SIZE; x1++) {
                    for (short y1 = 0; y1 < SUB_CHUNK_SIZE; y1++) {
                        for (short z1 = 0; z1 < SUB_CHUNK_SIZE; z1++) {

                            block currBlock = this->getBlock(x,y,z,x1,y1,z1);
                            int pos[]{(x<<6)+x,(y<<6)+y1,(z<<6)+z1};
                            
                            switch (x1) {
                                case SUB_CHUNK_SIZE-1:
                                    if (x == CHUNK_SUB_CHUNKS-1 || !this->getBlock(x+1,y,z,0,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,1);
                                    if (!this->getBlock(x,y,z,x1-1,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,0);
                                    break;
                                case 0:
                                    if (!x || !this->getBlock(x-1,y,z,0,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,0);
                                    if (!this->getBlock(x,y,z,x1+1,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,1);
                                    break;
                                default:
                                    if (!this->getBlock(x,y,z,x1+1,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,1);
                                    if (!this->getBlock(x,y,z,x1-1,y1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,1,0);
                                    break;
                            }

                            switch (y1) {
                                case SUB_CHUNK_SIZE-1:
                                    if (y == CHUNK_SUB_CHUNKS-1 || !this->getBlock(x,y+1,z,x1,0,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,1);
                                    if (!this->getBlock(x,y,z,x1,y1-1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,0);
                                    break;
                                case 0:
                                    if (!y || !this->getBlock(x,y-1,z,x1,0,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,0);
                                    if (!this->getBlock(x,y,z,x1,y1+1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,1);
                                    break;
                                default:
                                    if (!this->getBlock(x,y,z,x1,y1+1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,1);
                                    if (!this->getBlock(x,y,z,x1,y1-1,z1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,2,0);
                                    break;
                            }

                            switch (z1) {
                                case SUB_CHUNK_SIZE-1:
                                    if (z == CHUNK_SUB_CHUNKS-1 || !this->getBlock(x,y,z+1,x1,y1,0)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,1);
                                    if (!this->getBlock(x,y,z,x1,y1,z1-1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,0);
                                    break;
                                case 0:
                                    if (!z || !this->getBlock(x,y,z-1,x1,y1,0)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,0);
                                    if (!this->getBlock(x,y,z,x1,y1,z1+1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,1);
                                    break;
                                default:
                                    if (!this->getBlock(x,y,z,x1,y1,z1+1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,1);
                                    if (!this->getBlock(x,y,z,x1,y1,z1-1)) addFace(faces,pos[0],pos[1],pos[2],currBlock,0,0);
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, faces->size() * sizeof(face), faces->data(), GL_STATIC_DRAW);

    this->faces = faces->size();

    faces->clear();
    delete faces;
}

Chunk::Chunk(glm::ivec3* pos) {
    this->pos = pos;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0,1,GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), (void*)sizeof(GL_FLOAT));
    glEnableVertexAttribArray(1);

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

