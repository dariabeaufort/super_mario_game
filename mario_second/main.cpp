#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#include "object.hpp"
#include "game_state.hpp"
#include "collision.hpp"
#include "render.hpp"
#include "movement.hpp"
#include "level.hpp"

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

using jbeau::state::delete_moving;
using jbeau::state::get_new_brick;
using jbeau::state::get_new_moving;

using jbeau::collision::mario_collision;

using jbeau::level::create_level;

using jbeau::movement::horizon_move_map;
using jbeau::movement::horizon_move_object;
using jbeau::movement::player_dead;
using jbeau::movement::vert_move_object;

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