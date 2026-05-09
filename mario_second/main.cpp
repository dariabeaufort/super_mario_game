#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

using jbeau::object::Object;
using jbeau::object::set_object_pos;
using jbeau::object::init_object;

using namespace jbeau::state;

//static const int MAP_WIDTH = 80;
//static const int MAP_HEIGHT = 25;

static const float GRAVITY = 0.05f;
static const float JUMP_SPEED = -1.0f;
static const float GROUND_SPEED = 0.5f;
static const float MOVING_VERT_SPEED = -0.3f;

static const int DEAD_SCREEN_TIME_MS = 500;
static const int LVL_SWITCH_TIME_MS = 500;
static const int FRAME_SLEEP_MS = 10;

static const int SCORE_TEXT_X = 5;
static const int SCORE_TEXT_Y = 1;

static const int ENEMY_SCORE = 50;
static const int MONEY_SCORE = 100;

static const char PLAYER_SYMBOL = '@';

static const char ENEMY_SYMBOL = 'o';
static const char MONEY_SYMBOL = '$';

static const char BRICK_SYMBOL = '#';
static const char BONUS_BRICK_SYMBOL = '?';
static const char EMPTY_BRICK_SYMBOL = '-';
static const char FINISH_SYMBOL = '+';

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

bool is_collision(Object obj_1, Object obj_2);
void create_level(int lvl);
Object *get_new_moving();

void player_dead() {
	system("color 4F");
	Sleep(DEAD_SCREEN_TIME_MS);
	create_level(level);
}

void vert_move_object(Object *obj) {
	obj->is_fly = true;
	obj->vert_speed += GRAVITY;
	set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < brick_length; i++) {
		if (is_collision(*obj, brick[i])) {
			if (obj->vert_speed > 0) {
				obj->is_fly = false;
			}
			
			if ((brick[i].c_type == BONUS_BRICK_SYMBOL) 
				&& (obj->vert_speed < 0) 
			    && (obj == &mario)) {
				brick[i].c_type = EMPTY_BRICK_SYMBOL;
				init_object(get_new_moving(), brick[i].x, brick[i].y - 3, 3, 2, MONEY_SYMBOL);
				moving[moving_length - 1].vert_speed = MOVING_VERT_SPEED;
			}
			
			obj->y -= obj->vert_speed;
			obj->vert_speed = 0;

			if (brick[i].c_type == FINISH_SYMBOL) {
				level++;
				
				if (level > max_lvl) {
					level = 1;
				}
				
				system("color 2F");
				Sleep(LVL_SWITCH_TIME_MS);
				create_level(level);
			}
			break;
		}
	}
}

void delete_moving(int i) {
	moving_length--;
	moving[i] = moving[moving_length];
	moving = (Object*)realloc(moving, sizeof(*moving) * moving_length);
}

void mario_collision() {
	for (int i = 0; i < moving_length; i++) {
		if (is_collision(mario, moving[i])) {
			if (moving[i].c_type == ENEMY_SYMBOL) {
				if ((mario.is_fly == true) 
					&& (mario.vert_speed > 0) 
					&& (mario.y + mario.height 
					< moving[i].y + moving[i].height * 0.5)) {
					score += ENEMY_SCORE;
					delete_moving(i);
					i--;
					continue;
				} else {
					player_dead();
				}
			}
			
			if (moving[i].c_type == MONEY_SYMBOL) {
				score += MONEY_SCORE;
				delete_moving(i);
				i--;
				continue;
			}
		}
	}
}

void horizon_move_object(Object *obj) {
	obj->x += obj->horiz_speed;
	
	for (int i = 0; i < brick_length; i++) { 
		if (is_collision(*obj, brick[i])) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
			return;
		}
	}
	
	if (obj->c_type == ENEMY_SYMBOL) {
		Object tmp_obj = *obj;
		vert_move_object(&tmp_obj);
		
		if (tmp_obj.is_fly == true) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
		}
	}
}

bool is_pos_in_map(int x, int y) {
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
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

void horizon_move_map(float dx) {
	mario.x -= dx;
	for (int i = 0; i < brick_length; i++) {
		if (is_collision(mario, brick[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	
	for (int i = 0; i < brick_length; i++) {
		brick[i].x += dx;
	}
	
	for (int i = 0; i < moving_length; i++) {
		moving[i].x += dx;
	}
}

bool is_collision(Object obj_1, Object obj_2) {
	return ((obj_1.x + obj_1.width) > obj_2.x) 
		   && (obj_1.x < (obj_2.x + obj_2.width)) 
		   && ((obj_1.y + obj_1.height) > obj_2.y) 
		   && (obj_1.y < (obj_2.y + obj_2.height));
}

Object *get_new_brick() {
	brick_length++;
	brick = static_cast<Object*>(realloc(brick, sizeof(*brick) * brick_length));
	return brick + brick_length - 1;
}

Object *get_new_moving() {
	moving_length++;
	moving = static_cast<Object*>(realloc(moving, sizeof(*moving) * moving_length));
	return moving + moving_length - 1;
}

void put_score_on_map() {
	char score_text[30];
	sprintf(score_text, "Score: %d", score);
	const int len = strlen(score_text);
	for (int i = 0; i < len; i++) {
		map[SCORE_TEXT_Y][i + SCORE_TEXT_X] = score_text[i];
	}
}

void create_level(int lvl) {
	system("color DF");
	
	brick_length = 0;
	brick = static_cast<Object*>(realloc(brick, 0));
	moving_length = 0;
	moving = static_cast<Object*>(realloc(moving, 0));
	
	init_object(&mario, 39, 10, 3, 3, PLAYER_SYMBOL);
	score = 0;
	
	if (lvl == 1) {
		init_object(get_new_brick(), 20, 20, 40, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 15, 40, 10, BRICK_SYMBOL);
		init_object(get_new_brick(), 100, 20, 20, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 10, 10, BRICK_SYMBOL);
		init_object(get_new_brick(), 150, 20, 40, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 210, 15, 10, 10, FINISH_SYMBOL);
		
		init_object(get_new_brick(), 30, 10, 5, 3, BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 50, 10, 5, 3, BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 5, 10, 3, EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(), 70, 5, 5, 3, BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 75, 5, 5, 3, EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 5, 5, 3, BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 85, 5, 10, 3, EMPTY_BRICK_SYMBOL);
		
		init_object(get_new_moving(), 25, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, ENEMY_SYMBOL);
	}
	
	if (lvl == 2) {
		init_object(get_new_brick(), 20, 20, 40, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 15, 10, 10, BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 20, 20, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 10, 10, BRICK_SYMBOL);
		init_object(get_new_brick(), 150, 20, 40, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 210, 15, 10, 10, FINISH_SYMBOL);

		init_object(get_new_moving(), 25, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 65, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 120, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 160, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 175, 10, 3, 2, ENEMY_SYMBOL);
	}
	
	if (lvl == 3) {
		init_object(get_new_brick(), 20, 20, 40, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 20, 15, 5, BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 15, 10, BRICK_SYMBOL);
		init_object(get_new_brick(), 160, 10, 15, 15, FINISH_SYMBOL);

		init_object(get_new_moving(), 25, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 50, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 90, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 120, 10, 3, 2, ENEMY_SYMBOL);
		init_object(get_new_moving(), 130, 10, 3, 2, ENEMY_SYMBOL);
	}
	max_lvl = 3;
}

int main() {
	create_level(level);
	
	do {
		clear_map();
		
		if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) {
			mario.vert_speed = JUMP_SPEED;
		}
		if (GetKeyState('A') < 0) {
			horizon_move_map(1);
		}
		if (GetKeyState('D') < 0) {
			horizon_move_map(-1);
		}
		
		if (mario.y > MAP_HEIGHT) {
			player_dead();
		}
		
		vert_move_object(&mario);
		mario_collision();
		
		for (int i = 0; i < brick_length; i++) {
			put_object_on_map(brick[i]);
		}
		for (int i = 0; i < moving_length; i++) {
			vert_move_object(moving + i);
			horizon_move_object(moving + i);
			
			if (moving[i].y > MAP_HEIGHT) {
				delete_moving(i);
				i--;
				continue;
			}
			
			put_object_on_map(moving[i]);
		}
		put_object_on_map(mario);
		put_score_on_map();
		
		set_cur(0, 0);
		show_map();
		
		Sleep(FRAME_SLEEP_MS);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}