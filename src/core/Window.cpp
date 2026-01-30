#include "core/Window.h"
#include <iostream>

namespace AbyssCore{

    Window::Window(int width,int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title){
        init();
    }

    Window::~Window(){
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::init(){
        if(!glfwInit()){
            std::cout << "[ERROR] [CRITICO] Fallo al iniciar GLFW" << std::endl;
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Elegimos la versión CORE de OpenGL

        // Creamos la ventana
        m_window = glfwCreateWindow(m_width,m_height,m_title.c_str(),nullptr,nullptr);

        if(m_window == nullptr){
            std::cout << "[ERROR] [CRITICO] Fallo al crear ventana GLFW " << std::endl;
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(m_window);

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            std::cout << "[ERROR] [CRITICO] Fallo al inicializar GLAD " << std::endl;
            exit(-1);
        }

        glViewport(0,0,m_width,m_height);

        // Callback de redimensionado lambda
        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int w, int h){
            glViewport(0, 0, w, h);
            // Opcional: Actualizar m_width/m_height en la instancia
        });
    }


    /**
     * @brief Indica si la ventana ha recibido una solicitud de cierre.
     *
     * @return true si se ha solicitado cerrar la ventana, false en caso contrario.
     * @note Esta función es esencial para determinar cuándo finalizar el bucle principal de la aplicación.
     */
    bool Window::shouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    /**
     * @brief Intercambia los buffers frontal y trasero de la ventana.
     *
     * Actualiza el contenido visible de la ventana con el frame que se ha procesado en el buffer trasero.
     *
     * @return void.
     * @note Se debe invocar al final de cada iteración del bucle de renderizado para mostrar la imagen.
     */
    void Window::swapBuffers() {
        glfwSwapBuffers(m_window);
    }

    /**
     * @brief Procesa todos los eventos pendientes en la cola de eventos de GLFW.
     *
     * Consulta al sistema operativo por nuevos eventos (teclado, ratón, redimensionado) y actualiza el estado de la ventana.
     *
     * @return void.
     * @note Es fundamental llamar a esta función en cada iteración del bucle principal para evitar que la aplicación se bloquee.
     */
    void Window::pollEvents() {
        glfwPollEvents();
    }


}