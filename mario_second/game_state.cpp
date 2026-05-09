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
	}
}