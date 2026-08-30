#pragma once

#include "object.hpp"

namespace jbeau {
    namespace state {
        struct GameState;
    }
    namespace mario {
        class Mario : public jbeau::object::Object {
		private:
			bool alive;
			bool reached_finish;
        public:
            Mario();
			void spawn();
			void jump();
			void death();
			
			void vert_movement(jbeau::state::GameState& state);
			
			bool get_alive() const;
			bool get_reached_finish() const;
        };
    }
}