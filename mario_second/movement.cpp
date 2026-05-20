#include <stdlib.h>

#include <windows.h>

#include "movement.hpp"

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "object.hpp"

using jbeau::collision::is_collision;

using jbeau::level::create_level;

using jbeau::object::init_object;
using jbeau::object::Object;
using jbeau::object::set_object_pos;

using jbeau::state::brick;
using jbeau::state::brick_length;

using jbeau::state::map;
using jbeau::state::MAP_HEIGHT;

using jbeau::state::mario;

using jbeau::state::max_lvl;

using jbeau::state::moving;
using jbeau::state::moving_length;

using jbeau::state::get_new_moving;


void jbeau::movement::player_dead() {
	system("color 4F");
	Sleep(jbeau::state::DEAD_SCREEN_TIME_MS);
	create_level(jbeau::state::level);
}

void jbeau::movement::vert_move_object(Object *obj) {
	obj->is_fly = true;
	obj->vert_speed += jbeau::state::GRAVITY;
	set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < brick_length; i++) {
		if (is_collision(*obj, brick[i])) {
			if (obj->vert_speed > 0) {
				obj->is_fly = false;
			}
			
			if ((brick[i].c_type == jbeau::state::BONUS_BRICK_SYMBOL) 
				&& (obj->vert_speed < 0) 
			    && (obj == &mario)) {
				brick[i].c_type = jbeau::state::EMPTY_BRICK_SYMBOL;
				init_object(get_new_moving(), brick[i].x, brick[i].y - 3, 3, 2, jbeau::state::MONEY_SYMBOL);
				moving[moving_length - 1].vert_speed = jbeau::state::MOVING_VERT_SPEED;
			}
			
			obj->y -= obj->vert_speed;
			obj->vert_speed = 0;

			if (brick[i].c_type == jbeau::state::FINISH_SYMBOL) {
				jbeau::state::level++;
				
				if (jbeau::state::level > max_lvl) {
					jbeau::state::level = 1;
				}
				
				system("color 2F");
				Sleep(jbeau::state::LVL_SWITCH_TIME_MS);
				create_level(jbeau::state::level);
			}
			break;
		}
	}
}

void jbeau::movement::horizon_move_object(Object *obj) {
	obj->x += obj->horiz_speed;
	
	for (int i = 0; i < brick_length; i++) { 
		if (is_collision(*obj, brick[i])) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
			return;
		}
	}
	
	if (obj->c_type == jbeau::state::ENEMY_SYMBOL) {
		Object tmp_obj = *obj;
		jbeau::movement::vert_move_object(&tmp_obj);
		
		if (tmp_obj.is_fly == true) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
		}
	}
}

void jbeau::movement::horizon_move_map(float dx) {
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