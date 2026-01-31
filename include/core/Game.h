#ifndef GAME_H
#define GAME_H

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include "Window.h"

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

            std::unique_ptr<Window> m_window;

            // Control de hilos
            std::atomic<bool> m_isRunning;
            std::thread m_logicThread;

            // Sync
            std::mutex m_stateMutex;
    };
}
#endif