#include <windows.h>

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "movement.hpp"
#include "object.hpp"
#include "render.hpp"

int main() {
	jbeau::state::GameState state;
	jbeau::level::create_level(state, state.level);
	
	do {
		jbeau::render::clear_map(state);
		
		if ((state.mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) {
			state.mario.vert_speed = jbeau::state::JUMP_SPEED;
		}
		if (GetKeyState('A') < 0) {
			jbeau::movement::horizon_move_map(state, 1);
		}
		if (GetKeyState('D') < 0) {
			jbeau::movement::horizon_move_map(state, -1);
		}
		
		if (state.mario.y > jbeau::state::MAP_HEIGHT) {
			jbeau::movement::player_dead(state);
		}
		
		jbeau::movement::vert_move_object(state, &state.mario);
		jbeau::collision::mario_collision(state);
		
		for (int i = 0; i < state.brick_length; i++) {
			jbeau::render::put_object_on_map(state, state.brick[i]);
		}
		for (int i = 0; i < state.moving_length; i++) {
			jbeau::movement::vert_move_object(state, state.moving + i);
			jbeau::movement::horizon_move_object(state, state.moving + i);
			
			if (state.moving[i].y > jbeau::state::MAP_HEIGHT) {
				jbeau::state::delete_moving(state, i);
				i--;
				continue;
			}
			
			jbeau::render::put_object_on_map(state, state.moving[i]);
		}
		jbeau::render::put_object_on_map(state, state.mario);
		jbeau::render::put_score_on_map(state);
		
		jbeau::render::set_cur(0, 0);
		jbeau::render::show_map(state);
		
		Sleep(jbeau::state::FRAME_SLEEP_MS);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	free(state.brick);
	free(state.moving);
	
	return 0;
}