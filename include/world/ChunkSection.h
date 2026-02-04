#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H
#include <vector>
#include <atomic>
#include <array>
#include "BlockState.h"

namespace AbyssCore {
    //NOTA: constexpr puede evaluar en tiempo de compilación
    constexpr int CHUNK_SECTION_SIZE = 16;
    constexpr int CHUNK_SECTION_AREA = CHUNK_SECTION_SIZE * CHUNK_SECTION_SIZE;     // x*z
    constexpr int CHUNK_SECTION_VOLUME =  CHUNK_SECTION_AREA * CHUNK_SECTION_SIZE; // A*h

    class ChunkSection{
        public:
            ChunkSection(int yIndex);

            // Getters
            BlockID getBlock(int x, int y, int z) const;
            void setBlock(int x, int y, int z, BlockID block);

            // Estado
            bool isEmpty() const {}
            int getYIndex() const {}

        private:
            int m_yIndex;
            std::atomic<int> m_blockCount;
            std::array<std::atomic<BlockID>, CHUNK_SECTION_VOLUME> m_blocks;
    };

}



#endif // CHUNKSECTION_H