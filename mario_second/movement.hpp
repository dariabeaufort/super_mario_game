#pragma once

#include "object.hpp"

namespace jbeau {
	namespace movement {
		void player_dead(jbeau::state::GameState &state);

		void vert_move_object(jbeau::state::GameState &state, jbeau::object::Object *obj);
		void horizon_move_object(jbeau::state::GameState &state, jbeau::object::Object *obj);
		void horizon_move_map(jbeau::state::GameState &state, float dx);
	}
}