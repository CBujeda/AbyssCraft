#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @brief Ajusta el viewport de OpenGL cuando se cambia el tamaño de la ventana.
 * * Esta función actúa como un callback que actualiza las dimensiones del área de renderizado 
 * * para asegurar que la imagen se escale correctamente con la ventana.
 * @param window Puntero a la instancia de la ventana de GLFW que originó el evento.
 * @param width Nuevo ancho de la ventana en píxeles (debe ser mayor que 0).
 * @param height Nuevo alto de la ventana en píxeles (debe ser mayor que 0).
 * @return void
 * @note Es fundamental registrar esta función mediante glfwSetFramebufferSizeCallback para que se ejecute automáticamente.
 */
// Callback para cuando cmabiamos el tamaño de la pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

int main(){

    // Inicializamos GLFW y Configuramos 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Elegimos la versión CORE de OpenGL

    // Creamos la ventana
    GLFWwindow* window = glfwCreateWindow(854,480,"AbyssCraft",nullptr,nullptr);
    
    if(window == nullptr){
        std::cout << "[ERROR] Fallo al crear ventana GLFW " << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Metemos la ventana en el contexto actual
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    // Cargamos OpenGl (Con Galad)
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "[ERROR] Fallo al inicializar GLAD " << std::endl;
        return -1;
    }

    // GAME LOOP
    while(!glfwWindowShouldClose(window)){
        // ENTRADAS - INPUT
        if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window,true);
        }
        // RENDER
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);   // Estblecemos un color de fondo
        glClear(GL_COLOR_BUFFER_BIT);

        // Hacemos un Swap entre los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}