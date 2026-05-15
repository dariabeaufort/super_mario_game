#include <cstdio>
#include <cmath>
#include <windows.h>

#include "render.hpp"
#include "object.hpp"
#include "game_state.hpp"

using jbeau::state::map;
using jbeau::state::MAP_WIDTH;
using jbeau::state::MAP_HEIGHT;
using jbeau::state::score;
using jbeau::object::Object;

// temporary dependencies (to be refactored later)
static const int SCORE_TEXT_X = 5;
static const int SCORE_TEXT_Y = 1;

namespace jbeau {
	namespace render {
		bool is_pos_in_map(int x, int y) {
			return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
		}
		
		void clear_map() {
			for (int i = 0; i < MAP_WIDTH; i++) {
				map[0][i] = ' ';
			}
			map[0][MAP_WIDTH] = '\0';
			
			for (int j = 1; j < MAP_HEIGHT; j++) {
				sprintf(map[j], map[0]);
			}
		}

		void show_map() {
			map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
			for (int j = 0; j < MAP_HEIGHT; j++) {
				printf("%s", map[j]);
			}
		}

		void put_object_on_map(Object obj) {
			int ix = static_cast<int>(round(obj.x));
			int iy = static_cast<int>(round(obj.y));
			int i_width = static_cast<int>(round(obj.width));
			int i_height = static_cast<int>(round(obj.height));
			
			for (int i = ix; i < (ix + i_width); i++) {
				for (int j = iy; j < (iy + i_height); j++) {
					if (is_pos_in_map(i, j)) {
						map[j][i] = obj.c_type;
					}
				}
			}
		}

		void set_cur(int x, int y) {
			COORD coord;
			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}

		void put_score_on_map() {
			char score_text[30];
			sprintf(score_text, "Score: %d", score);
			const int len = strlen(score_text);
			for (int i = 0; i < len; i++) {
				map[SCORE_TEXT_Y][i + SCORE_TEXT_X] = score_text[i];
			}
		}
	}
}