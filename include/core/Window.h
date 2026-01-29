#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace AbyssCore {
    /**
     * @class Window
     * @brief Gestiona la creación, ciclo de vida y renderizado de una ventana del sistema mediante GLFW.
     * >  * Actúa como un envoltorio (wrapper) sobre la API nativa de GLFW para abstraer la configuración del contexto gráfico y la gestión de eventos. 
     * >  * Es responsable de inicializar la ventana y liberar los recursos asociados al destruir la instancia.
     * >  * @note No es Thread-Safe; las operaciones de la ventana y el manejo de eventos deben ocurrir preferiblemente en el hilo principal.
     */
    class Window {
        public:
            Window(int width,int height, const std::string& title);
            ~Window();

            /**
             * @brief Prohíbe la duplicación de la instancia de la ventana.
             * * Al marcar el constructor de copia y el operador de asignación como 'delete', 
             * se evita que el compilador permita copiar objetos Window. Esto garantiza que 
             * solo exista un único dueño del puntero GLFWwindow (semántica de entidad).
             * * @param const Window& Referencia al objeto que se intentaría copiar.
             * @return Window& (En el caso del operador de asignación).
             * @note Evita errores críticos como la doble liberación de memoria (double free) 
             * al cerrar la ventana en el destructor.
             */
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            bool shouldClose() const;
            void swapBuffers();
            void pollEvents();

            // Getters

            GLFWwindow* getNativeWindow() const { return m_window; }
            int getWidth() const {return m_width;}
            int getHeight() const { return m_height; }

        private:
            GLFWwindow* m_window = nullptr;
            int m_width;
            int m_height;
            std::string m_title;

            void init();
    };
}



#endif // WINDOW_H