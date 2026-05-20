#pragma once

#include "object.hpp"

namespace jbeau {
	namespace render {
		bool is_pos_in_map(int x, int y);
		void clear_map();
		void show_map();
		void set_cur(int x, int y);
		void put_object_on_map(const jbeau::object::Object &obj);
		void put_score_on_map();
	}
}