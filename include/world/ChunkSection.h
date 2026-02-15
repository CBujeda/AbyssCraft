#ifndef CHUNKSECTION_H
#define CHUNKSECTION_H
#include <vector>
#include <atomic>
#include <array>
#include "BlockState.h"

namespace AbyssCore {
    //NOTA: constexpr puede evaluar en tiempo de compilación
    constexpr int CHUNK_SECTION_SIZE = 16;
    constexpr int CHUNK_SECTION_SIZE_LOG2 = 4;  // Para divisiones con shifts
    // Máscara de bits para obtener el resto (16 - 1 = 15)
    // En binario: 00001111, permite extraer los 4 bits menos significativos
    constexpr int CHUNK_SECTION_MASK = CHUNK_SECTION_SIZE - 1;

    constexpr int CHUNK_SECTION_LAYER = CHUNK_SECTION_SIZE * CHUNK_SECTION_SIZE;     // x*z
    constexpr int CHUNK_SECTION_LAYER_LOG2 = 8;      // log2(16 * 16), para movernos una capa (Y)
    
    
    constexpr int CHUNK_SECTION_VOLUME =  CHUNK_SECTION_LAYER * CHUNK_SECTION_LAYER; // A*h

    class ChunkSection{
        public:
            ChunkSection(int yIndex);

            // Getters
            BlockID getBlock(int x, int y, int z) const;
            void setBlock(int x, int y, int z, BlockID block);
            /**/
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