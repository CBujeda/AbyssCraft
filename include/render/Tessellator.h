#ifndef TESSELLATOR_H
#define TESSELLATOR_H
#include <vector>
#include <cstddef>
#include <glm/glm.hpp>
#include <render/Shader.h>
#include <glad/glad.h>
namespace AbyssCore {
    
    /**
     * Estructura empaquetada para la GPU
     * 
     */
    struct Vertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoords;
    };

    /**
     * @class Tessellator
     * @brief Clase encargada de la acumulación y renderizado eficiente de primitivas geométricas.
     * 
     * Proporciona una interfaz para definir vértices, colores y coordenadas UV en un búfer intermedio (CPU) que luego se transfiere de forma masiva a la GPU. 
     * Gestiona internamente la memoria de video mediante objetos VAO y VBO, optimizando las llamadas de dibujo.
     * 
     * @note Sigue el patrón Singleton para acceso global. No es Thread-Safe; las operaciones de dibujo deben realizarse en el hilo principal de renderizado.
     */
    class Tessellator {
        public:
            static Tessellator& getInstance();

            Tessellator(std::size_t bufferSize = 2097152); // Default 2MB
            ~Tessellator();

            // Ciclo de Dibujo
            void startDrawing();
            void draw();

            // Definición de vertices
            void addVertex(float x, float y, float z);
            void addVertexWithUV(float x, float y, float z, float u, float v);

            // Estado
            void setColor(float r, float g, float b, float a = 1.0f);
            void setTranslation(float x, float y, float z);
        private:
            void initRednderData();
            void flush(); // Envia datoa a GPU en caso de que el buffer se llene

            // Datos CPU
            std::vector<Vertex> m_buffer;
            std::size_t m_maxVertices;

            // Estado actual
            glm::vec4 m_currentColor;
            glm::vec3 m_translation;
            bool m_isDrawing;
            
            // OpenGL Objects
            unsigned int VAO, VBO;

            // Stats
            int m_verticesCount;
    };
}


#endif // TESSELLATOR_H
