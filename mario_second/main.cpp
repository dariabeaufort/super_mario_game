#include <windows.h>

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "movement.hpp"
#include "object.hpp"
#include "render.hpp"

using jbeau::state::mario;
using jbeau::state::brick;
using jbeau::state::moving;

int main() {
	jbeau::level::create_level(jbeau::state::level);
	
	do {
		jbeau::render::clear_map();
		
		if ((mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) {
			mario.vert_speed = jbeau::state::JUMP_SPEED;
		}
		if (GetKeyState('A') < 0) {
			jbeau::movement::horizon_move_map(1);
		}
		if (GetKeyState('D') < 0) {
			jbeau::movement::horizon_move_map(-1);
		}
		
		if (mario.y > jbeau::state::MAP_HEIGHT) {
			jbeau::movement::player_dead();
		}
		
		jbeau::movement::vert_move_object(&mario);
		jbeau::collision::mario_collision();
		
		for (int i = 0; i < jbeau::state::brick_length; i++) {
			jbeau::render::put_object_on_map(brick[i]);
		}
		for (int i = 0; i < jbeau::state::moving_length; i++) {
			jbeau::movement::vert_move_object(moving + i);
			jbeau::movement::horizon_move_object(moving + i);
			
			if (moving[i].y > jbeau::state::MAP_HEIGHT) {
				jbeau::state::delete_moving(i);
				i--;
				continue;
			}
			
			jbeau::render::put_object_on_map(moving[i]);
		}
		jbeau::render::put_object_on_map(mario);
		jbeau::render::put_score_on_map();
		
		jbeau::render::set_cur(0, 0);
		jbeau::render::show_map();
		
		Sleep(jbeau::state::FRAME_SLEEP_MS);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}