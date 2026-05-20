#pragma once

#include "object.hpp"

namespace jbeau {
	namespace render {
		bool is_pos_in_map(int x, int y);
		void clear_map(jbeau::state::GameState &state);
		void show_map(jbeau::state::GameState &state);
		void set_cur(int x, int y);
		void put_object_on_map(jbeau::state::GameState &state, 
							   const jbeau::object::Object &obj);
		void put_score_on_map(jbeau::state::GameState &state);
	}
}