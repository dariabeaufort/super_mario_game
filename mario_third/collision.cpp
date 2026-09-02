#include "collision.hpp"

#include "game_state.hpp"

bool jbeau::collision::is_collision(
	const jbeau::object::Object &obj_1,
	const jbeau::object::Object &obj_2
) {
	return ((obj_1.x + obj_1.width) > obj_2.x)
		   && (obj_1.x < (obj_2.x + obj_2.width))
		   && ((obj_1.y + obj_1.height) > obj_2.y)
		   && (obj_1.y < (obj_2.y + obj_2.height));
}