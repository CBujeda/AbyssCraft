#include "core/Game.h"


namespace AbyssCore {
    Game::Game() : m_running(true){
        m_window = std::make_unique<Window>(800,600,"AbyssCraft");
    }

    Game::~Game(){

    }

    void Game::run(){

        while(m_running && !m_window->shouldClose()){
            update();
            render();


            m_window->pollEvents();
            m_window->swapBuffers();
        }
    }

    void Game::update(){
        if(glfwGetKey(m_window->getNativeWindow(),GLFW_KEY_ESCAPE) == GLFW_PRESS){
            m_running = false;
        }
    }

    void Game::render(){
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Depth buffer es importante para 3D
    }

}