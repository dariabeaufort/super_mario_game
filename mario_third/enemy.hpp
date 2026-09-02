#pragma once

#include "brick.hpp"
#include "object.hpp"

namespace jbeau {
	namespace enemy {
        class Enemy : public jbeau::object::Object {

        public:
            Enemy();
			~Enemy() = default;

            void spawn(float x_pos, float y_pos);
            void vert_movement(jbeau::brick::Brick* bricks,int brick_length);
            void horizon_movement(jbeau::brick::Brick* bricks, int brick_length);
        };	
	}
}