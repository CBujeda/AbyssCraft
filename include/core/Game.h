#ifndef GAME_H
#define GAME_H

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include "Window.h"
#include "render/Shader.h"
#include "render/Tessellator.h"
#include <iostream>

namespace AbyssCore {
    class Game {
        public:
            Game();
            ~Game();

            void run();
        private:
            // --- Hilo Principal (Render & Input) ---
            void renderLoop();

            // --- Hilo de Lógica
            void logicLoop();

            // --- Hilo de Física/Mundo
            void worldLoop();

            // Render Assets
            std::unique_ptr<Shader> m_shader; // unique_ptr, para gestión automatica de memoria

            std::unique_ptr<Window> m_window;

            // Control de hilos
            std::atomic<bool> m_isRunning;
            std::thread m_logicThread;

            // Sync
            std::mutex m_stateMutex;

            // State
            float m_triangleX = 0.0f;  // Pfición X Calculada en Logic
            float m_triangleSpeed = 0.1f;// Velocidad
    };
}
#endif