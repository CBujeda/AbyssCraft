#include "core/Game.h"
#include "core/Config.h"
#include <string>
#include <cstring>

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
/**
 * @brief Procesa los argumentos de la línea de comandos para configurar los parámetros iniciales del juego.
 * 
 * Recorre los argumentos pasados al programa y actualiza la instancia única de configuración 
 * con los valores proporcionados para el ancho, alto y título de la ventana.
 * 
 * @param argc Cantidad de argumentos recibidos desde la terminal (debe ser al menos 1).
 * @param argv Arreglo de cadenas de caracteres que contiene los argumentos.
 * @return void
 * @note Soporta las banderas -w (ancho), -h (alto) y -title (título). Se asume que los valores numéricos son válidos.
 */
void parseArgs(int argc, char* argv[]){
    AbyssCore::Config& config = AbyssCore::Config::getInstance();
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            config.width = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            config.height = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "-title") == 0 && i + 1 < argc) {
            config.title = argv[++i];
        }
    }
}


int main(int argc, char* argv[]){
    parseArgs(argc, argv);
    AbyssCore::Game abyssCraft;
    // Ejecutamos
    abyssCraft.run();

    return 0;
}