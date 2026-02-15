#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>
#include <vector>
#include <string>
#include <unordered_map> // Estructura diccionario o hash


namespace AbyssCore {
    class  TextureManager {
        public:
            static TextureManager& getInstance() {
                static TextureManager instance;
                return instance;
            }

            // Load de las texturas y generación de array de datos
            void loadTextures();
            
            // Retorno de del indice de la capa segun un nombre
            int getTextureLayer(const std::string& name);
            
            // Inicio de la textura en el shader
            void bind();
        private:
            TextureManager() = default;

            unsigned int m_textureID;
            std::unordered_map<std::string,int> m_textureMap;

            const int TEXTURE_WIDTH = 16;
            const int TEXTURE_HEIGHT = 16;
        
        
    };
    

    
}




#endif
