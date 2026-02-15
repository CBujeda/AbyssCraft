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
        // Identificamos el indice de la sección que 
        // pertenece a la altura worldY 
        int sectionIndex = worldY >> CHUNK_SECTION_SIZE_LOG2;
        // Identificamos la altura dentro de la sección
        int localY = worldY & CHUNK_SECTION_MASK; // Hacemos un modulo 16, usando una mascara

        ChunkSection* section = getSection(sectionIndex);
        section->setBlock(relX,localY,relZ,block);
        // CONTINUAR
    }

    BlockID ChunkColumn::getBlock(int relX,int worldY,int relZ){
        // Bit shift >> 4 es dividir por 16.
        // Identificamos el indice de la sección que 
        // pertenece a la altura worldY 
        int sectionIndex = worldY >> CHUNK_SECTION_SIZE_LOG2;
        // Identificamos la altura dentro de la sección
        int localY = worldY & CHUNK_SECTION_MASK; // Hacemos un modulo 16, usando una mascara
        // Si la sección no existe, retornamos aire
        std::lock_guard<std::mutex> lock(m_columnMutex);
        SectionIterator it = m_sections.find(sectionIndex);
        if (it != m_sections.end()) {
            return it->second->getBlock(relX, localY, relZ);
        }
        return 0; // Aire
    }

}