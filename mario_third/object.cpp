#include "object.hpp"

#include "game_state.hpp"

void jbeau::object::Object::set_pos(float x_pos, float y_pos) {
	x = x_pos;
	y = y_pos;
}

void jbeau::object::Object::init(float x_pos, float y_pos, 
								float obj_width, float obj_height, 
								char in_type) {
	set_pos(x_pos, y_pos);
	width = obj_width;
	height = obj_height;
	vert_speed = 0;
	c_type = in_type;
	horiz_speed = jbeau::state::GROUND_SPEED;
}