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
			state.mario.jump();
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
		
		state.mario.vert_movement(state);
		
		if (state.mario.get_reached_finish()) {
			state.level++;
			
			if (state.level > state.max_lvl) {
				state.level = 1;
			}
			
			system("color 2F");
			Sleep(jbeau::state::LVL_SWITCH_TIME_MS);
			
			jbeau::level::create_level(state, state.level);
			continue;
		}
		
		for (int i = 0; i < state.brick_length; i++) {
			jbeau::render::put_object_on_map(state, state.brick[i]);
		}
		
		for (int i = 0; i < state.enemy_length; i++) {
			state.enemy[i].vert_movement(state.brick, state.brick_length);
			state.enemy[i].horizon_movement(state.brick, state.brick_length);
		}
		
		for (int i = 0; i < state.enemy_length; i++) {
			if (state.mario.up_enemy_collision(state.enemy[i])) {
				state.score += jbeau::state::ENEMY_SCORE;
				jbeau::state::delete_enemy(state, i);
				i--;
				continue;
			}
			
			if (state.mario.enemy_collision(state.enemy[i])) {
				state.mario.death();
				break;
			}
		}
		
		if (!state.mario.get_alive()) {
			jbeau::movement::player_dead(state);
			continue;
		}
		
		for (int i = 0; i < state.money_length; i++) {
			state.money[i].vert_movement(state.brick, state.brick_length);
			state.money[i].horizon_movement(state.brick, state.brick_length);
		}
		
		for (int i = 0; i < state.money_length; i++) {
			if (state.mario.money_collision(state.money[i])) {
				state.score += jbeau::state::MONEY_SCORE;
				jbeau::state::delete_money(state, i);
				i--;
				continue;
			}
		}
		
		for (int i = 0; i < state.enemy_length; i++) {
			jbeau::render::put_object_on_map(state, state.enemy[i]);
		}
		
		for (int i = 0; i < state.money_length; i++) {
			jbeau::render::put_object_on_map(state, state.money[i]);
		}
		
		jbeau::render::put_object_on_map(state, state.mario);
		
		jbeau::render::put_score_on_map(state);
		
		jbeau::render::set_cur(0, 0);
		jbeau::render::show_map(state);
		
		Sleep(jbeau::state::FRAME_SLEEP_MS);
		
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	delete[] state.brick;
	delete[] state.enemy;
	delete[] state.money;
	
	return 0;
}