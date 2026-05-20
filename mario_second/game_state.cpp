#include <cstdlib>

#include "game_state.hpp"

using jbeau::state::moving_length;
using jbeau::state::brick_length;
using jbeau::state::moving;
using jbeau::state::brick;

char jbeau::state::map[MAP_HEIGHT][MAP_WIDTH + 1];

jbeau::object::Object jbeau::state::mario;

jbeau::object::Object *jbeau::state::brick = nullptr;
int jbeau::state::brick_length = 0;

jbeau::object::Object *jbeau::state::moving = nullptr;
int jbeau::state::moving_length = 0;

int jbeau::state::level = 1;
int jbeau::state::score = 0;
int jbeau::state::max_lvl = 0;

void jbeau::state::delete_moving(int i) {
	moving_length--;
	moving[i] = moving[moving_length];
	moving = static_cast<jbeau::object::Object*>(
			 realloc(moving, sizeof(*moving) * moving_length));
}

jbeau::object::Object *jbeau::state::get_new_brick() {
	brick_length++;
	brick = static_cast<jbeau::object::Object*>(
			realloc(brick, sizeof(*brick) * brick_length));
	return brick + brick_length - 1;
}

jbeau::object::Object *jbeau::state::get_new_moving() {
	moving_length++;
	moving = static_cast<jbeau::object::Object*>(
			 realloc(moving, sizeof(*moving) * moving_length));
	return moving + moving_length - 1;
}