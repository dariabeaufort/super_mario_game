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


int main() {
	create_level(level);
	
	do {
		clear_map();
		
		if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) {
			mario.vert_speed = jbeau::state::JUMP_SPEED;
		}
		if (GetKeyState('A') < 0) {
			horizon_move_map(1);
		}
		if (GetKeyState('D') < 0) {
			horizon_move_map(-1);
		}
		
		if (mario.y > jbeau::state::MAP_HEIGHT) {
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
			
			if (moving[i].y > jbeau::state::MAP_HEIGHT) {
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
		
		Sleep(jbeau::state::FRAME_SLEEP_MS);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}