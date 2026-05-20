#include "game_state.hpp"

#include "object.hpp"

void jbeau::object::set_object_pos(jbeau::object::Object *obj,
									float x_pos, float y_pos) {
	obj->x = x_pos;
	obj->y = y_pos;
}

void jbeau::object::init_object(jbeau::object::Object *obj, 
								float x_pos, float y_pos, 
								float obj_width, float obj_height, 
								char in_type) {
	set_object_pos(obj, x_pos, y_pos);
	obj->width = obj_width;
	obj->height = obj_height;
	obj->vert_speed = 0;
	obj->c_type = in_type;
	obj->horiz_speed = jbeau::state::GROUND_SPEED;
}