#pragma once

#include "object.hpp"

namespace jbeau {
	namespace movement {
		void player_dead();

		void vert_move_object(jbeau::object::Object *obj);
		void horizon_move_object(jbeau::object::Object *obj);
		void horizon_move_map(float dx);
	}
}