#include "render/Tessellator.h"
#include <iostream>
#include <cstddef>

namespace AbyssCore {
    
    Tessellator& Tessellator::getInstance() {
        static Tessellator instance;
        return instance;
    }
    
    /**
     * @brief Inicializa el Tessellator con un tamaño de búfer específico.
     *
     * Calcula la capacidad máxima de vértices basándose en el tamaño en bytes proporcionado y reserva el espacio necesario en memoria.
     *
     * @param bufferSize Tamaño total en bytes para el búfer de vértices. Debe ser mayor a 0.
     * @return void
     * @note Realiza una reserva de memoria inmediata e invoca la inicialización de datos de renderizado.
     */
    Tessellator::Tessellator(std::size_t bufferSize)
        : m_maxVertices(bufferSize / sizeof(AbyssCore::Vertex)),
          m_currentColor(1.0f),
          m_translation(0.0f),
          m_isDrawing(false),
          m_verticesCount(0)
    {
        m_buffer.reserve(m_maxVertices);
        initRednderData();
    }
    
    Tessellator::~Tessellator() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    
    /**
     * @brief Configura los objetos de renderizado de OpenGL (VAO y VBO).
     *
     * Genera los manejadores de buffers, reserva memoria de video de forma dinámica y define el layout de los atributos del vértice (posición, color y UV).
     *
     * @return void
     * @note Se utiliza GL_DYNAMIC_DRAW ya que los datos de los vértices se actualizan frecuentemente en cada frame.
     */
    void Tessellator::initRednderData() {
        // Configurar VAO y VBO con OpenGL Moderno
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);  
        
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Reservamos memoria en GPU, usamos DINAMIC_DRAW ya que
        // cambiamos en cada frame
        glBufferData(GL_ARRAY_BUFFER, m_maxVertices * sizeof(AbyssCore::Vertex), nullptr,GL_DYNAMIC_DRAW);

        // 1. Posición (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // 2. Color (location = 1)
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(1);

        // 3. UV (location = 2)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
        glEnableVertexAttribArray(2);
        
    }

    void Tessellator::startDrawing(){
        if(m_isDrawing){
            std::cerr << " Tessellator is already drawing" << std::endl;
            return;
        }
        m_isDrawing = true;
        m_verticesCount = 0;
        m_buffer.clear();
    }

    void Tessellator::addVertex(float x, float y, float z){
        addVertexWithUV(x,y,z,0.0f,0.0f);
    }

    void Tessellator::addVertexWithUV(float x, float y, float z,float u, float v){
        Vertex vtx;

        vtx.position = glm::vec3(x + m_translation.x, y + m_translation.y, z + m_translation.z);
        vtx.color = m_currentColor;
        vtx.texCoords = glm::vec2(u,v);

        m_buffer.push_back(vtx);
        m_verticesCount++;

        // Auto-flush si nos pasamos de memoria (como el check de bufferSize en Java)
        if (m_buffer.size() >= m_maxVertices) {
            draw();
            startDrawing();
        }
    }

    void Tessellator::setColor(float r, float g, float b, float a){
        m_currentColor = glm::vec4(r,g,b,a);
    }

    void Tessellator::setTranslation(float x, float y, float z){
        m_translation = glm::vec3(x,y,z);
    }

    /**
     * @brief Finaliza el proceso de dibujo y envía los datos acumulados a la GPU.
     *
     * Transfiere los vértices del búfer de CPU a la memoria de video mediante glBufferSubData y ejecuta la llamada de dibujo (draw call) utilizando GL_TRIANGLES.
     *
     * @return void
     * @note Si no se está dibujando o el búfer está vacío, la función aborta la operación de forma segura. Al finalizar, el estado de dibujo se marca como falso.
     */
    void Tessellator::draw(){
        if(!m_isDrawing || m_buffer.empty()){
            m_isDrawing = false;
            return;
        }
        // GPU UPLOAD
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Subimos solo los vértices que hemos añadido
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_buffer.size() * sizeof(Vertex), m_buffer.data());

        // --- DRAW CALL ---
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, m_verticesCount); // Usaremos Triangulos por defecto
        glBindVertexArray(0);
        m_isDrawing = false;
    }
}