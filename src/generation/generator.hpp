#ifndef _WorldGen
#define _WorldGen

struct Chunk;

class Generator {

    public:
        void generateChunk(Chunk* chunk);

        Generator();
        ~Generator();
};

#endif
