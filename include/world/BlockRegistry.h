#ifndef BLOCKREGISTRY_H
#define BLOCKREGISTRY_H
#include <string>
#include <vector>
#include "BlockState.h"

namespace AbyssCore {

    struct BlockType {
        std::string name;
        int textureTop;
        int textureSide;
        int textureBottom;
        bool isTransparent; // Optimización de renderizado para hojas y cristal
    };

    class BlockRegistry {
        public:
            static BlockRegistry& getInstance(){
                static BlockRegistry i;
                return i;
            } 
            void init();
            const BlockType& getBlock(BlockID id) const;
        private:
            std::vector<BlockType> m_blocks;

    };
}
#endif