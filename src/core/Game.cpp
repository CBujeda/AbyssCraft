#include "core/Game.h"


namespace AbyssCore {
    Game::Game() : m_isRunning(true){
        m_window = std::make_unique<Window>(800,600,"AbyssCraft");
        m_shader = std::make_unique<Shader>("assets/shaders/core.vert", "assets/shaders/core.frag");
    }

    Game::~Game(){
        m_isRunning = false;
        if(m_logicThread.joinable()){
            m_logicThread.join(); // Esperamos a que el hilo de logica termine antes de cerrar, para no dejar hijos en el SO
            std::cout << "[System] Logic thread joined safely." << std::endl;
        }
    }

    void Game::run(){
        m_logicThread = std::thread(&Game::logicLoop,this); // Iniciamos el Hilo de logica
        renderLoop();   // Iniciamos el render en el hilo principal
    }

    void Game::renderLoop(){
        std::cout << "[System] Render Thread Started" << std::endl;
        Tessellator& tessellator = Tessellator::getInstance();
        while(m_isRunning && !m_window->shouldClose()){
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Leemos el estado del mundo-> Metido en un mutex

            m_shader->use();
            float currentX = 0;
            {
                std::lock_guard<std::mutex> lock(m_stateMutex);
                currentX = m_triangleX;
                // renderWorld();
            }
            // ------------ TEST DIBUJO TRIANGULO
            // 4. Dibujar usando Tessellator
            tessellator.startDrawing();
            
            tessellator.setColor(0.0f, 1.0f, 0.5f, 1.0f); // Verde Cyan

            // Dibujamos un triángulo usando la posición calculada por el otro hilo
            // Vértice 1 (Arriba)
            tessellator.addVertex(currentX, 0.5f, 0.0f);
            
            // Vértice 2 (Abajo Derecha)
            tessellator.setColor(1.0f, 0.0f, 0.5f, 1.0f); // Gradiente
            tessellator.addVertex(currentX + 0.5f, -0.5f, 0.0f);
            
            // Vértice 3 (Abajo Izquierda)
            tessellator.setColor(0.0f, 0.5f, 1.0f, 1.0f); // Gradiente
            tessellator.addVertex(currentX - 0.5f, -0.5f, 0.0f);

            tessellator.draw();
            // ------------- FIN TEST

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
                // --- Inicio Sección Critica
                {
                    std::lock_guard<std::mutex> lock(m_stateMutex);
                    m_triangleX += m_triangleSpeed;
                    if(m_triangleX >0.8f || m_triangleX < -0.8f){
                        m_triangleSpeed *= -1.0f; // Rebote
                    }
                    // world->tick();
                    // player->tick();
                    // physics->update();
                }
                // --- Fin sección critica
                delta -= nsPerTick;

            } else {
                // Dormimos para liberar CPU, en caso de no necesitarla
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }

}