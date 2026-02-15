#include "world/BlockRegistry.h"
#include "render/TextureManager.h"

namespace AbyssCore {

    void BlockRegistry::init(){
        
        // ID 0 : Air
        TextureManager& tex = TextureManager::getInstance();
        m_blocks.push_back({
            "Air",0,0,0,true
        });

        // ID 1 : Stone
        int stoneTex = tex.getTextureLayer("dirt");
        m_blocks.push_back({
            "Stone",stoneTex,stoneTex,stoneTex,false
        });

        // ID 2 : Dirt
        int dirtTex = tex.getTextureLayer("dirt");
        m_blocks.push_back({
            "Dirt",dirtTex,dirtTex,dirtTex,false
        });

        // ID 3 : Grass
        int grassTopTex = tex.getTextureLayer("grass");
        int grassSideTex = tex.getTextureLayer("grass_side");
        m_blocks.push_back({
            "Grass",grassTopTex,grassSideTex,dirtTex,false
        });

        // ID 4 : Log
        int log_topTex = tex.getTextureLayer("log_top");
        int logTex = tex.getTextureLayer("log");
        m_blocks.push_back({
            "Log",log_topTex,logTex,log_topTex,false
        });

        // ID 5 : Leaves
        int leavesTex = tex.getTextureLayer("leaves");
        m_blocks.push_back({
            "Leaves",leavesTex,leavesTex,leavesTex,true
        });

        int coalTex = tex.getTextureLayer("coal_ore");
        m_blocks.push_back({
            "Coal",coalTex,coalTex,coalTex,false
        });

        int ironTex = tex.getTextureLayer("iron_ore");
        m_blocks.push_back({
            "Iron",ironTex,ironTex,ironTex,false
        });
    }

    //    const BlockType& BlockRegistry

}