#include "render/Tessellator.h"
#include <iostream>
#include <cstddef>

namespace AbyssCore {
    
    /**
     * @brief Obtiene la instancia única de la clase Tessellator.
     * 
     * Implementa el patrón Singleton para asegurar que solo exista un gestor de vértices en todo el ciclo de vida de la aplicación.
     * 
     * @return Tessellator& Referencia a la instancia única global.
     * @note Al ser una variable estática local, se inicializa de forma segura en el primer acceso (Thread-safe en C++11).
     */
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
    
    /**
     * @brief Destructor de la clase Tessellator.
     *
     * Libera los recursos de OpenGL (VAO y VBO) almacenados en la GPU para evitar fugas de memoria de video.
     *
     * @return void
     * @note Se invoca automáticamente al destruir la instancia o al finalizar el programa.
     */
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

    /**
     * @brief Prepara el Tessellator para comenzar a recibir datos de vértices.
     *
     * Reinicia el contador de vértices y limpia el búfer interno de la CPU. Si ya se estaba dibujando, emite un error por consola.
     *
     * @return void
     * @note Debe llamarse antes de cualquier operación de adición de vértices (addVertex).
     */
    void Tessellator::startDrawing(){
        if(m_isDrawing){
            std::cerr << " Tessellator is already drawing" << std::endl;
            return;
        }
        m_isDrawing = true;
        m_verticesCount = 0;
        m_buffer.clear();
    }

    /**
     * @brief Agrega un vértice al búfer con las coordenadas espaciales proporcionadas.
     * 
     * Esta función es una simplificación de addVertexWithUV que establece las coordenadas de textura (UV) por defecto en (0,0).
     * 
     * @param x Coordenada en el eje X.
     * @param y Coordenada en el eje Y.
     * @param z Coordenada en el eje Z.
     * @return void
     * @note La posición final será desplazada por el vector de traslación actual del Tessellator.
     */
    void Tessellator::addVertex(float x, float y, float z){
        addVertexWithUV(x,y,z,0.0f,0.0f);
    }

    /**
     * @brief Agrega un vértice al búfer incluyendo coordenadas de textura (UV).
     *
     * Crea un vértice aplicando la traslación actual, el color configurado y las coordenadas UV proporcionadas. Si el búfer alcanza su capacidad máxima, se realiza un volcado (flush) automático a la GPU.
     *
     * @param x Coordenada X de la posición.
     * @param y Coordenada Y de la posición.
     * @param z Coordenada Z de la posición.
     * @param u Coordenada horizontal de la textura (normalmente entre 0.0 y 1.0).
     * @param v Coordenada vertical de la textura (normalmente entre 0.0 y 1.0).
     * @return void
     * @note La posición final se ve afectada por el vector de traslación definido previamente en setTranslation.
     */
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

    /**
     * @brief Establece el color actual para los próximos vértices.
     * 
     * Define los componentes RGBA que se aplicarán a cada vértice añadido posteriormente mediante addVertex.
     * 
     * @param r Componente rojo (rango sugerido 0.0 a 1.0).
     * @param g Componente verde (rango sugerido 0.0 a 1.0).
     * @param b Componente azul (rango sugerido 0.0 a 1.0).
     * @param a Componente alfa/opacidad (rango sugerido 0.0 a 1.0).
     * @return void
     */
    void Tessellator::setColor(float r, float g, float b, float a){
        m_currentColor = glm::vec4(r,g,b,a);
    }

    /**
     * @brief Define un vector de traslación global para la geometría.
     * 
     * @param x Desplazamiento en el eje X.
     * @param y Desplazamiento en el eje Y.
     * @param z Desplazamiento en el eje Z.
     * @return void
     * @note Este valor se suma a la posición de cada vértice en el momento de ser añadido al búfer.
     */
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