#pragma once

#include "game_state.hpp"

namespace jbeau {
    namespace game {
        class Game {
        private:
            jbeau::state::GameState state;

            bool is_running;

            void input();
            void horizon_move_map(float dx);
            void update();
            void handle_collisions();
            void player_dead();
            void next_level();
            void show();

        public:
            Game();
			~Game();

            void init();
            void run();
            void stop();
        };
    }
}