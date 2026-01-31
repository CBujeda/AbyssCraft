#include "core/Game.h"


namespace AbyssCore {
    Game::Game() : m_isRunning(true){
        m_window = std::make_unique<Window>(800,600,"AbyssCraft");
    }

    Game::~Game(){
        m_isRunning = false;
        if(m_logicThread.joinable()){
            m_logicThread.join(); // Esperamos a que el hilo de logica termine antes de cerrar, para no dejar hijos en el SO
        }
    }

    void Game::run(){
        m_logicThread = std::thread(&Game::logicLoop,this); // Iniciamos el Hilo de logica
        renderLoop();   // Iniciamos el render en el hilo principal
    }

    void Game::renderLoop(){
        while(m_isRunning && !m_window->shouldClose()){
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Leemos el estado del mundo-> Metido en un mutex
            {
                std::lock_guard<std::mutex> lock(m_stateMutex);
                // renderWorld();
            }
            m_window->swapBuffers();
            m_window->pollEvents();
        }
        m_isRunning = false;  // Si cerramos, paramos
    }

    void Game::logicLoop(){
        // Funcionamiento a 20 ticks por segundo (50ms por tick)
        const double nsPerTick = 1000000000.0 / 20.0;
        auto lastTime = std::chrono::steady_clock::now();
        double delta = 0;

        while(m_isRunning){
            std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
            delta += std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime).count();
            lastTime = now;

            if (delta >= nsPerTick) {
                // Logica x Tick
                {
                    std::lock_guard<std::mutex> lock(m_stateMutex);
                    // world->tick();
                    // player->tick();
                    // physics->update();
                }
                delta -= nsPerTick;

            } else {
                // Dormimos para liberar CPU, en caso de no necesitarla
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }

}