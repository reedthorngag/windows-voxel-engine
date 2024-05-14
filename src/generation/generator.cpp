#include <random>
#include <math.h>

#include "noise.hpp"
#include "generator.hpp"
#include "../chunk.hpp"
#include "../globals.hpp"


void Generator::generateChunk(Chunk* chunk) {

    for (int x = 0; x < CHUNK_SUB_CHUNKS; x++) {
        for (int z = 0; z < CHUNK_SUB_CHUNKS; z++) {
            
            subChunk* subChunk = new struct subChunk;

            for (int x1 = 0; x1 < SUB_CHUNK_SIZE; x1++) {
                for (int z1 = 0; z1 < SUB_CHUNK_SIZE; z1++) {

                    double input1 = chunk->pos->x*CHUNK_SIZE + x*SUB_CHUNK_SIZE + x1;
                    double input2 = chunk->pos->z*CHUNK_SIZE + z*SUB_CHUNK_SIZE + z1;

                    int y = (int)round((genNoise(input1,input2)) + 4);

                    subChunk->blocks[x1][y][z1] = block::GRASS;
                    
                }
            }
        }
    }
}

Generator::Generator() {

}

Generator::~Generator() {

}

