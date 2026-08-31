#pragma once

#include "object.hpp"
#include "brick.hpp"

namespace jbeau {
	namespace money {
		class Money : public jbeau::object::Object {
		
		public:
			Money();
			
			void spawn(float x_pos, float y_pos);
			void vert_movement(jbeau::brick::Brick* bricks, int brick_length);
			void horizon_movement(jbeau::brick::Brick* bricks, int brick_length);
        };	
	}
}