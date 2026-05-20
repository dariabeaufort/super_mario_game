#include <stdlib.h>

#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

#include "level.hpp"

using jbeau::object::init_object;

using jbeau::state::get_new_brick;
using jbeau::state::get_new_moving;

void jbeau::level::create_level(int lvl) {
	system("color DF");
	
	jbeau::state::brick_length = 0;
	jbeau::state::brick = static_cast<jbeau::object::Object*>(
						  realloc(jbeau::state::brick, 0));

	jbeau::state::moving_length = 0;
	jbeau::state::moving = static_cast<jbeau::object::Object*>(
						   realloc(jbeau::state::moving, 0));
	
	init_object(&jbeau::state::mario, 39, 10, 3, 3, jbeau::state::PLAYER_SYMBOL);
	jbeau::state::score = 0;
	
	if (lvl == 1) {
		init_object(get_new_brick(), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 15, 40, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 100, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);
		
		init_object(get_new_brick(), 30, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 50, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(), 70, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 75, 5, 5, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(), 85, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		
		init_object(get_new_moving(), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
	}
	
	if (lvl == 2) {
		init_object(get_new_brick(), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 60, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);

		init_object(get_new_moving(), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 65, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 160, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 175, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
	}
	
	if (lvl == 3) {
		init_object(get_new_brick(), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 80, 20, 15, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 120, 15, 15, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(), 160, 10, 15, 15, jbeau::state::FINISH_SYMBOL);

		init_object(get_new_moving(), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 50, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 90, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(), 130, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
	}
	
	jbeau::state::max_lvl = 3;
}