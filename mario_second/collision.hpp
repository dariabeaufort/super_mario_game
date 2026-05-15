#pragma once

#include "object.hpp"

namespace jbeau {
	namespace collision {
		bool is_collision(
			jbeau::object::Object obj_1,
			jbeau::object::Object obj_2
		);
	}
}