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
                printf("generating sub chunk, x: %d y: %d z: %d ",x,y,z);
                printf("k");
                fflush(stdout);
                //SubChunk* subChunk = new struct SubChunk;
                block (*subChunk)[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE] = new block[SUB_CHUNK_SIZE][SUB_CHUNK_SIZE][SUB_CHUNK_SIZE]{};
                printf("k");
                fflush(stdout);
                bool chunkSolid = true;
                bool solidStone = false;
                bool solidAir = false;

                for (int x1 = 0; x1 < SUB_CHUNK_SIZE-1; x1++) {
                    for (int z1 = 0; z1 < SUB_CHUNK_SIZE; z1++) {

                        double input1 = chunk->pos->x*CHUNK_SIZE + x*SUB_CHUNK_SIZE + x1;
                        double input2 = chunk->pos->z*CHUNK_SIZE + z*SUB_CHUNK_SIZE + z1;

                        // printf("a ");
                        // fflush(stdout);

                        int y1 = (int)round((genNoise(input1,input2)) + 4);

                        // printf("x1: %d z1: %d y1: %d ",x1,z1,y1);
                        // fflush(stdout);
                        
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

                        // printf("here ");
                        // fflush(stdout);

                        int relY = y1 & 0x3ff;

                        subChunk[x1][relY][z1] = block::GRASS;

                        for (int i = 3; i-- && relY;) 
                            subChunk[x1][--relY][z1] = block::DIRT;

                        for (;relY--;)
                            subChunk[x1][relY][z1] = block::STONE;
                        
                        // printf("here\n");
                    }
                }

                if (chunkSolid && (solidStone != solidAir)) {
                    printf("a ");
                    fflush(stdout);
                    chunk->subChunks[x][y][z] = (SubChunk)(subChunk[0][0][0] & (1LL<<63));
                    printf("empty chunk!\n");
                } else {
                    printf("b ");
                    fflush(stdout);
                    chunk->subChunks[x][y][z] = subChunk;
                    printf("added chunk!\n");
                }
            }
        }
    }
}

Generator::Generator() {

}

Generator::~Generator() {

}

