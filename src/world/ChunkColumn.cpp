#include "world/ChunkColumn.h"

namespace AbyssCore {
    // Definiciones
    using SectionIterator = std::unordered_map<int, std::unique_ptr<ChunkSection>>::iterator;
    //Unique ptr nos garantiza que un solo objeto sea dueño de la
    //  sección del chunk e memoria. Además de liberarse de la memoria
    //  de forma automatica.
    using SectionPtr = std::unique_ptr<ChunkSection>;
    
    
    ChunkColumn::ChunkColumn(int x, int z) : x(x),z(z){}

    ChunkSection* ChunkColumn::getSection(int yIndex){
        std::lock_guard<std::mutex> lock(m_columnMutex);
        // Buscamos la sección que nos piden
        SectionIterator it = m_sections.find(yIndex);
        if(it != m_sections.end()){
            return it->second.get();    // Devolvemos la sección
        }

        // En caso de que no exista la sección la creamos
        SectionPtr newSection = std::make_unique<ChunkSection>(yIndex);
        ChunkSection* ptr = newSection.get();
        m_sections[yIndex] = std::move(newSection); // Movemos el puntero a la lista de secciones
        return ptr;
    }

    void ChunkColumn::setBlock(int relX,int worldY, int relZ, BlockID block){
        // Bit shift >> 4 es dividir por 16.
        int sectionIndex = worldY >> CHUNK_SECTION_SIZE_LOG2;
        int localY = worldY & CHUNK_SECTION_MASK; // Hacemos un modulo 16, usando una mascara


        // CONTINUAR
    }

}