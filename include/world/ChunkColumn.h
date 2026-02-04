#ifndef CHUNKCOLUMN_H
#define CHUNKCOLUMN_H
#include <unordered_map>
#include <memory>
#include <mutex>
#include "ChunkSection.h"

namespace AbyssCore{

    class ChunkColumn {
        public:
            const int x, z;

            ChunkColumn(int x, int z);

            // Coordenadas mundiales relativas al chunk
            // Ejemplo: setBlock(5, 150, 5, Stone) -> Busca la sección Y=9
            void setBlock(int relX,int worldY, int relZ, BlockID block);
            BlockID getBlock(int relX, int worldY, int relZ);


            ChunkSection* getSection(int yIndex);


            // Es necesario Mutex para añadir secciones verticales
            std::mutex m_columnMutex;
        private:
            // Hashmap para las secciones negativas y alturas infinitas
            std::unordered_map<int,std::unique_ptr<ChunkSection>> m_sections;

    };



}


#endif  // CHUNKCOLUMN_H
