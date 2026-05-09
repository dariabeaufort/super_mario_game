#pragma once

#include "object.hpp"

namespace jbeau {
	namespace state {
		// temporary dependencies (to be refactored later)
		static const int MAP_WIDTH = 80;
		static const int MAP_HEIGHT = 25;
		
		extern char map[MAP_HEIGHT][MAP_WIDTH + 1];
		extern jbeau::object::Object mario;

		extern jbeau::object::Object *brick;
		extern int brick_length;

		extern jbeau::object::Object *moving;
		extern int moving_length;

		extern int level;
		extern int score;
		extern int max_lvl;
	}
}