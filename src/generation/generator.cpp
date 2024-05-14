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
                double input1 = (chunk->pos->x*CHUNK_SIZE+x);
                double input2 = (chunk->pos->y*CHUNK_SIZE+z);
                int y =  (int)round((genNoise(input1,input2)) + 4);

                
            }
        }
    }
}

Generator::Generator() {

}

Generator::~Generator() {

}

