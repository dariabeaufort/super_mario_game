#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#include "object.hpp"
#include "game_state.hpp"
#include "collision.hpp"
#include "render.hpp"

using jbeau::object::Object;
using jbeau::object::set_object_pos;
using jbeau::object::init_object;

using jbeau::state::map;
using jbeau::state::mario;
using jbeau::state::brick;
using jbeau::state::brick_length;
using jbeau::state::moving;
using jbeau::state::moving_length;
using jbeau::state::level;
using jbeau::state::score;
using jbeau::state::max_lvl;

using jbeau::state::MAP_WIDTH;
using jbeau::state::MAP_HEIGHT;

using jbeau::collision::is_collision;

using jbeau::render::is_pos_in_map;
using jbeau::render::clear_map;
using jbeau::render::show_map;
using jbeau::render::set_cur;
using jbeau::render::put_object_on_map;
using jbeau::render::put_score_on_map;

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