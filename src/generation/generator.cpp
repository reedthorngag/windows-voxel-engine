#include <random>
#include <math.h>

#include "noise.hpp"
#include "generator.hpp"
#include "../chunk.hpp"
#include "../globals.hpp"


void Generator::generateChunk(Chunk* chunk) {

    for (int x = 0; x < CHUNK_SUB_CHUNKS; x++) {
        for (int y = 0; y < CHUNK_SUB_CHUNKS; y++) {
            for (int z = 0; z < CHUNK_SUB_CHUNKS; z++) {
                block (*subChunk)[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE] = new block[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE][SUB_CHUNK_SIZE]{};
                bool chunkSolid = true;
                bool solidStone = false;
                bool solidAir = false;

                for (int x1 = 0; x1 < SUB_CHUNK_SIZE; x1++) {
                    for (int z1 = 0; z1 < SUB_CHUNK_SIZE; z1++) {

                        double input1 = chunk->pos->x*CHUNK_SIZE + x*SUB_CHUNK_SIZE + x1;
                        double input2 = chunk->pos->z*CHUNK_SIZE + z*SUB_CHUNK_SIZE + z1;

                        int y1 = (int)round((genNoise(input1,input2)) + 4);
                        
                        int subChunkY = y1>>6;
                        if (subChunkY < y) {
                            for (int y2 = SUB_CHUNK_SIZE; y2--;)
                                subChunk[x1][y2][z1] = block::STONE;
                            solidStone = true;
                            continue;
                        }
                        else if (subChunkY > y) {
                            solidAir = true;
                            continue;
                        }
                        else chunkSolid = false;

                        int relY = y1 & 0x3f;

                        subChunk[x1][relY][z1] = block::GRASS;

                        for (int i = 3; i-- && relY;) 
                            subChunk[x1][--relY][z1] = block::DIRT;

                        for (;relY--;)
                            subChunk[x1][relY][z1] = block::STONE;
                        
                    }
                }

                if (chunkSolid && (solidStone != solidAir))
                    chunk->subChunks[x][y][z] = (SubChunk)(subChunk[0][0][0] & (1LL<<63));
                else chunk->subChunks[x][y][z] = subChunk;
            }
        }
    }
}

Generator::Generator() {

}

Generator::~Generator() {

}

