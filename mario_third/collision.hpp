#pragma once

#include "game_state.hpp"
#include "object.hpp"

namespace jbeau {
	namespace collision {
		bool is_collision(
			const jbeau::object::Object &obj_1,
			const jbeau::object::Object &obj_2
		);
	}
}