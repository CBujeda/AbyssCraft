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

        //glViewport()
    }


}