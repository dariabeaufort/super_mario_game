#include <stdlib.h>

#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

#include "level.hpp"

using jbeau::object::init_object;

void jbeau::level::create_level(jbeau::state::GameState &state, int lvl) {
	system("color DF");
	
	state.brick_length = 0;
	state.brick = static_cast<jbeau::object::Object*>(realloc(state.brick, 0));

	state.moving_length = 0;
	state.moving = static_cast<jbeau::object::Object*>(realloc(state.moving, 0));
	
	init_object(&state.mario, 39, 10, 3, 3, jbeau::state::PLAYER_SYMBOL);
	state.score = 0;
	
	switch(lvl) {
		case 1:
		init_object(get_new_brick(state), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 60, 15, 40, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 100, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);
		
		init_object(get_new_brick(state), 30, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(state), 50, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(state), 60, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(state), 70, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(state), 75, 5, 5, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		init_object(get_new_brick(state), 80, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		init_object(get_new_brick(state), 85, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		
		init_object(get_new_moving(state), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		break;
		
		case 2:
		init_object(get_new_brick(state), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 60, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 80, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);

		init_object(get_new_moving(state), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 65, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 160, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 175, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		break;
		
		case 3:
		init_object(get_new_brick(state), 20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 80, 20, 15, 5, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 120, 15, 15, 10, jbeau::state::BRICK_SYMBOL);
		init_object(get_new_brick(state), 160, 10, 15, 15, jbeau::state::FINISH_SYMBOL);

		init_object(get_new_moving(state), 25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 50, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 90, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		init_object(get_new_moving(state), 130, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		
		lvl = 1;
		break;
	}
	
	state.max_lvl = 3;
}