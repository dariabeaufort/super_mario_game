#pragma once

namespace jbeau {
	namespace object {
		struct Object {
			float x, y;
			float width, height;
			float vert_speed;
			bool is_fly;
			char c_type;
			float horiz_speed;
		};
		
		void set_object_pos(Object *obj, float x_pos, float y_pos);
		void init_object(Object *obj,
						 float x_pos, float y_pos, 
						 float obj_width, float obj_height, 
						 char in_type);
	}
}