#include <cstdlib>

#include <windows.h>

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "object.hpp"

#include "movement.hpp"

using jbeau::state::brick;
using jbeau::state::moving;

void jbeau::movement::player_dead() {
	system("color 4F");
	Sleep(jbeau::state::DEAD_SCREEN_TIME_MS);
	jbeau::level::create_level(jbeau::state::level);
}

void jbeau::movement::vert_move_object(jbeau::object::Object *obj) {
	obj->is_fly = true;
	obj->vert_speed += jbeau::state::GRAVITY;
	jbeau::object::set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < jbeau::state::brick_length; i++) {
		if (jbeau::collision::is_collision(*obj, brick[i])) {
			if (obj->vert_speed > 0) {
				obj->is_fly = false;
			}
			
			if ((brick[i].c_type == jbeau::state::BONUS_BRICK_SYMBOL) 
				&& (obj->vert_speed < 0) 
			    && (obj == &jbeau::state::mario)) {
				brick[i].c_type = jbeau::state::EMPTY_BRICK_SYMBOL;
				jbeau::object::init_object(jbeau::state::get_new_moving(), 
										   brick[i].x, brick[i].y - 3, 3, 2, 
										   jbeau::state::MONEY_SYMBOL);
				moving[jbeau::state::moving_length - 1].vert_speed = jbeau::state::MOVING_VERT_SPEED;
			}
			
			obj->y -= obj->vert_speed;
			obj->vert_speed = 0;

			if (brick[i].c_type == jbeau::state::FINISH_SYMBOL) {
				jbeau::state::level++;
				
				if (jbeau::state::level > jbeau::state::max_lvl) {
					jbeau::state::level = 1;
				}
				
				system("color 2F");
				Sleep(jbeau::state::LVL_SWITCH_TIME_MS);
				jbeau::level::create_level(jbeau::state::level);
			}
			break;
		}
	}
}

void jbeau::movement::horizon_move_object(jbeau::object::Object *obj) {
	obj->x += obj->horiz_speed;
	
	for (int i = 0; i < jbeau::state::brick_length; i++) { 
		if (jbeau::collision::is_collision(*obj, brick[i])) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
			return;
		}
	}
	
	if (obj->c_type == jbeau::state::ENEMY_SYMBOL) {
		jbeau::object::Object tmp_obj = *obj;
		jbeau::movement::vert_move_object(&tmp_obj);
		
		if (tmp_obj.is_fly == true) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
		}
	}
}

void jbeau::movement::horizon_move_map(float dx) {
	jbeau::state::mario.x -= dx;
	for (int i = 0; i < jbeau::state::brick_length; i++) {
		if (jbeau::collision::is_collision(jbeau::state::mario, brick[i])) {
			jbeau::state::mario.x += dx;
			return;
		}
	}
	jbeau::state::mario.x += dx;
	
	for (int i = 0; i < jbeau::state::brick_length; i++) {
		brick[i].x += dx;
	}
	
	for (int i = 0; i < jbeau::state::moving_length; i++) {
		moving[i].x += dx;
	}
}