#include "world/ChunkSection.h"

namespace AbyssCore {

    ChunkSection::ChunkSection(int yIndex)
    : m_yIndex(yIndex), m_blockCount(0) {
        // Ponemos todos los bloques a aire
        for (std::atomic<BlockID>& b : m_blocks) {
            b = 0;
        }
    }

    void ChunkSection::setBlock(int x, int y, int z, BlockID block){
        // Índice plano: (y * 16 * 16) + (z * 16) + x
        int index = (y << CHUNK_SECTION_LAYER_LOG2) | (z << CHUNK_SECTION_SIZE_LOG2) | x;
        
        BlockID oldBlock = m_blocks[index].exchange(block); // Cambio seguro ante threads
        
        // Actualización de bloques vacios
        if(oldBlock == 0 && block != 0){
            m_blockCount++;
        }else if(oldBlock != 0 && block == 0){
            m_blockCount--;
        }
    
    }

    BlockID ChunkSection::getBlock(int x, int y, int z) const  {
            int index = (y << CHUNK_SECTION_LAYER_LOG2) | (z << CHUNK_SECTION_SIZE_LOG2) | x;
            return m_blocks[index].load();
    }

}