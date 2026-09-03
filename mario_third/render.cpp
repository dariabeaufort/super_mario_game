#include "render.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

using namespace jbeau;

render::Render::Render() {
    for (int i = 0; i < state::MAP_HEIGHT; i++) {
		for (int j = 0; j < state::MAP_WIDTH; j++) {
			map[i][j] = ' ';
		}
		map[i][state::MAP_WIDTH] = '\0';
	}
}

render::Render::~Render() {
    
}

bool render::Render::is_pos_in_map(int x, int y) const {
	return ((x >= 0) && (x < state::MAP_WIDTH) 
		   && (y >= 0) && (y < state::MAP_HEIGHT));
}

void render::Render::clear_map() {
	for (int i = 0; i < state::MAP_WIDTH; i++) {
		map[0][i] = ' ';
	}
	map[0][state::MAP_WIDTH] = '\0';
	
	for (int j = 1; j < state::MAP_HEIGHT; j++) {
		std::sprintf(map[j], map[0]);
	}
}

void render::Render::show_map() {
	map[state::MAP_HEIGHT - 1][state::MAP_WIDTH - 1] = '\0';
	for (int j = 0; j < state::MAP_HEIGHT; j++) {
		std::printf("%s", map[j]);
	}
}

void render::Render::put_object_on_map(const object::Object &obj) {
	int ix = static_cast<int>(round(obj.x));
	int iy = static_cast<int>(round(obj.y));
	int i_width = static_cast<int>(round(obj.width));
	int i_height = static_cast<int>(round(obj.height));
	
	for (int i = ix; i < (ix + i_width); i++) {
		for (int j = iy; j < (iy + i_height); j++) {
			if (render::Render::is_pos_in_map(i, j)) {
				map[j][i] = obj.c_type;
			}
		}
	}
}

void render::Render::set_cur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void render::Render::put_score_on_map(int score) {
	char score_text[30];
	std::sprintf(score_text, "Score: %d", score);
	const int len = std::strlen(score_text);
	for (int i = 0; i < len; i++) {
		map[state::SCORE_TEXT_Y][i + state::SCORE_TEXT_X] = score_text[i];
	}
}