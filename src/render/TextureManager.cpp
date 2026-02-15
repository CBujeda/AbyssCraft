#include "render/TextureManager.h"

#include <stb/stb_image.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;



namespace AbyssCore {

    void TextureManager::loadTextures(){
        // Lista de texturas
        // NOTA: Esto mas adelante lo cogeremos del sistema
        std::vector<std::string> textures = {
            "stone", "dirt", "grass", "grass_side", 
            "coal_ore", "iron_ore", "log", "log_top", "leaves"
        };

        //Creación del texture array
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D_ARRAY,m_textureID);
        //Reserva de memoria
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // Cargamos imagen oor imagen
        for (int i = 0; i < textures.size(); i++){
            std::string path = "assets/textures/blocks/" + textures[i] + ".png";
            int width, height, nrChannels;
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4); // Forzar 4 canales (RGBA)
            if(data){
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
            
                m_textureMap[textures[i]] = i;
                stbi_image_free(data);
            }else{
                std::cerr << "Failed to load texture: " << path << std::endl;
            }
        }

        // PArametros
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Pixel art nítido
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Generamos mipmaps
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }

    int TextureManager::getTextureLayer(const std::string& name){
        if(m_textureMap.find(name) != m_textureMap.end()){
            return m_textureMap[name];  // Recogemos la textura correcta
        }
        return 0; // Devolvemos el bloque default (stone)
    }

    void TextureManager::bind(){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY,m_textureID);
    }
}