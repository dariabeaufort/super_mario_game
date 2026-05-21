#include <cstdlib>

#include "game_state.hpp"

void jbeau::state::delete_moving(GameState &state, int i) {
	state.moving_length--;
	state.moving[i] = state.moving[state.moving_length];
	state.moving = static_cast<jbeau::object::Object*>(
			 realloc(state.moving, sizeof(*state.moving) * state.moving_length));
}

jbeau::object::Object *jbeau::state::get_new_brick(GameState &state) {
	state.brick_length++;
	state.brick = static_cast<jbeau::object::Object*>(
			realloc(state.brick, sizeof(*state.brick) * state.brick_length));
	return state.brick + state.brick_length - 1;
}

jbeau::object::Object *jbeau::state::get_new_moving(GameState &state) {
	state.moving_length++;
	state.moving = static_cast<jbeau::object::Object*>(
			 realloc(state.moving, sizeof(*state.moving) * state.moving_length));
	return state.moving + state.moving_length - 1;
}