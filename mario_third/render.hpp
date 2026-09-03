#pragma once

#include "game_state.hpp"
#include "object.hpp"

namespace jbeau {
	namespace render {
		class Render {
			private:
				char map[jbeau::state::MAP_HEIGHT][jbeau::state::MAP_WIDTH + 1];
				bool is_pos_in_map(int x, int y) const;
			public:
				Render();
				~Render();
				void clear_map();
				void show_map();
				void set_cur(int x, int y);
				void put_object_on_map(const jbeau::object::Object &obj);
				void put_score_on_map(int score);
		};
	}
}