#include "collision.hpp"

#include "game_state.hpp"

using namespace jbeau;

bool collision::is_collision(
	const object::Object &obj_1,
	const object::Object &obj_2
) {
	return ((obj_1.x + obj_1.width) > obj_2.x)
		   && (obj_1.x < (obj_2.x + obj_2.width))
		   && ((obj_1.y + obj_1.height) > obj_2.y)
		   && (obj_1.y < (obj_2.y + obj_2.height));
}