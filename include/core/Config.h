#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace AbyssCore{
    struct Config{
        int width;
        int height;
        std::string title = "AbyssCraft";
        std::string version = "Alpha 0.0.1";

        /**
         * @brief Obtiene la instancia única de la configuración del motor.
         *
         * Implementa el patrón Singleton para garantizar un único punto de acceso global a los ajustes.
         *
         * @return Referencia a la instancia estática de la estructura Config.
         * @note La inicialización es perezosa (lazy initialization) y segura para hilos según el estándar C++11.
         */
        static Config& getInstance() {
            static Config instance;
            return instance;
        }
    };
}

#endif // CONFIG_H