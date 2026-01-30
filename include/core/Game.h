#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Window.h"

namespace AbyssCore {
    class Game {
        public:
            Game();
            ~Game();

            void run();
        private:
            void update();
            void render();

            std::unique_ptr<Window> m_window;
            bool m_running;
    };
}
#endif