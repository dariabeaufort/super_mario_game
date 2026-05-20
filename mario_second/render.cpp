#include <cmath>
#include <cstdio>
#include <cstring>

#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

#include "render.hpp"

bool jbeau::render::is_pos_in_map(int x, int y) {
	return ((x >= 0) && (x < jbeau::state::MAP_WIDTH) 
		   && (y >= 0) && (y < jbeau::state::MAP_HEIGHT));
}

void jbeau::render::clear_map() {
	for (int i = 0; i < jbeau::state::MAP_WIDTH; i++) {
		jbeau::state::map[0][i] = ' ';
	}
	jbeau::state::map[0][jbeau::state::MAP_WIDTH] = '\0';
	
	for (int j = 1; j < jbeau::state::MAP_HEIGHT; j++) {
		sprintf(jbeau::state::map[j], jbeau::state::map[0]);
	}
}

void jbeau::render::show_map() {
	jbeau::state::map[jbeau::state::MAP_HEIGHT - 1][jbeau::state::MAP_WIDTH - 1] = '\0';
	for (int j = 0; j < jbeau::state::MAP_HEIGHT; j++) {
		printf("%s", jbeau::state::map[j]);
	}
}

void jbeau::render::put_object_on_map(const jbeau::object::Object &obj) {
	int ix = static_cast<int>(round(obj.x));
	int iy = static_cast<int>(round(obj.y));
	int i_width = static_cast<int>(round(obj.width));
	int i_height = static_cast<int>(round(obj.height));
	
	for (int i = ix; i < (ix + i_width); i++) {
		for (int j = iy; j < (iy + i_height); j++) {
			if (jbeau::render::is_pos_in_map(i, j)) {
				jbeau::state::map[j][i] = obj.c_type;
			}
		}
	}
}

void jbeau::render::set_cur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void jbeau::render::put_score_on_map() {
	char score_text[30];
	sprintf(score_text, "Score: %d", jbeau::state::score);
	const int len = std::strlen(score_text);
	for (int i = 0; i < len; i++) {
		jbeau::state::map[jbeau::state::SCORE_TEXT_Y][i + jbeau::state::SCORE_TEXT_X] = score_text[i];
	}
}