#include <cstdlib>

#include <windows.h>

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "object.hpp"

#include "movement.hpp"

void jbeau::movement::player_dead(jbeau::state::GameState &state) {
	system("color 4F");
	Sleep(jbeau::state::DEAD_SCREEN_TIME_MS);
	jbeau::level::create_level(state, state.level);
}

void jbeau::movement::vert_move_object(jbeau::state::GameState &state, 
									   jbeau::object::Object *obj) {
	obj->is_fly = true;
	obj->vert_speed += jbeau::state::GRAVITY;
	obj->set_pos(obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < state.brick_length; i++) {
		if (jbeau::collision::is_collision(*obj, state.brick[i])) {
			if (obj->vert_speed > 0) {
				obj->is_fly = false;
			}
			
			obj->y -= obj->vert_speed;
			obj->vert_speed = 0;

			if (state.brick[i].c_type == jbeau::state::FINISH_SYMBOL) {
				state.level++;
				
				if (state.level > state.max_lvl) {
					state.level = 1;
				}
				
				system("color 2F");
				Sleep(jbeau::state::LVL_SWITCH_TIME_MS);
				jbeau::level::create_level(state, state.level);
			}
			break;
		}
	}
}

void jbeau::movement::horizon_move_object(jbeau::state::GameState &state, 
										  jbeau::object::Object *obj) {
	obj->x += obj->horiz_speed;
	
	for (int i = 0; i < state.brick_length; i++) { 
		if (jbeau::collision::is_collision(*obj, state.brick[i])) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
			return;
		}
	}
	
	if (obj->c_type == jbeau::state::ENEMY_SYMBOL) {
		jbeau::object::Object tmp_obj = *obj;
		jbeau::movement::vert_move_object(state, &tmp_obj);
		
		if (tmp_obj.is_fly == true) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
		}
	}
}

void jbeau::movement::horizon_move_map(jbeau::state::GameState &state, float dx) {
	state.mario.x -= dx;
	for (int i = 0; i < state.brick_length; i++) {
		if (jbeau::collision::is_collision(state.mario, state.brick[i])) {
			state.mario.x += dx;
			return;
		}
	}
	state.mario.x += dx;
	
	for (int i = 0; i < state.brick_length; i++) {
		state.brick[i].x += dx;
	}
	
	for (int i = 0; i < state.enemy_length; i++) {
		state.enemy[i].x += dx;
	}

	for (int i = 0; i < state.money_length; i++) {
		state.money[i].x += dx;
	}
}