#include "core/Game.h"


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

// Creamos el juego en el Stack
    AbyssCore::Game abyssCraft;
    
    // Ejecutamos
    abyssCraft.run();

    return 0;
}