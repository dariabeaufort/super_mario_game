#pragma once

#include "brick.hpp"
#include "enemy.hpp"
#include "money.hpp"
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
			float prev_y;
			int hit_brick_from_below;
        public:
            Mario();
			~Mario() = default;
			void spawn();
			void jump();
			void death();
			void gravity();
			
			void vert_movement(jbeau::state::GameState& state);
			
			bool enemy_collision(const jbeau::enemy::Enemy& enemy) const;
			bool up_enemy_collision(const jbeau::enemy::Enemy& enemy) const;
			bool money_collision(const jbeau::money::Money& money) const;
			
			bool get_alive() const;
			bool get_reached_finish() const;
			float get_prev_y() const;
			int get_hit_brick_from_below() const;
        };
    }
}