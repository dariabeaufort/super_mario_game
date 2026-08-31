#pragma once

#include "object.hpp"

namespace jbeau {
	namespace brick {
		
		enum class BrickType {
			BRICK = '#',
			BONUS = '?',
			EMPTY = '-',
			FINISH = '+'
		};
		
		class Brick : public jbeau::object::Object {
			private:
				BrickType brick_type;
				bool was_hit;
			public:
				Brick();
				
				void spawn(float x_pos, float y_pos,
						   float obj_width, float obj_height,
						   BrickType type);
				
				void hit();
				
				BrickType get_type() const;
				bool is_finish() const;
		};
	}
}