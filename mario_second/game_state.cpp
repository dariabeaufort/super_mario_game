#include <stdlib.h>

#include "game_state.hpp"

namespace jbeau {
	namespace state {
		char map[MAP_HEIGHT][MAP_WIDTH + 1];

		jbeau::object::Object mario;

		jbeau::object::Object *brick = nullptr;
		int brick_length = 0;

		jbeau::object::Object *moving = nullptr;
		int moving_length = 0;

		int level = 1;
		int score = 0;
		int max_lvl = 0;
		
		void delete_moving(int i) {
			moving_length--;
			moving[i] = moving[moving_length];
			moving = (jbeau::object::Object*)realloc(moving, sizeof(*moving) * moving_length);
		}
		
		jbeau::object::Object *get_new_brick() {
			brick_length++;
			brick = static_cast<jbeau::object::Object*>(realloc(brick, sizeof(*brick) * brick_length));
			return brick + brick_length - 1;
		}

		jbeau::object::Object *get_new_moving() {
			moving_length++;
			moving = static_cast<jbeau::object::Object*>(realloc(moving, sizeof(*moving) * moving_length));
			return moving + moving_length - 1;
		}
	}
}