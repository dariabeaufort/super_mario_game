#include <stdlib.h>

#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

#include "level.hpp"

void jbeau::level::create_level(jbeau::state::GameState &state, int lvl) {
	system("color DF");
	
	state.brick_length = 0;
	state.brick = static_cast<jbeau::object::Object*>(realloc(state.brick, 0));

	state.moving_length = 0;
	state.moving = static_cast<jbeau::object::Object*>(realloc(state.moving, 0));
	
	state.mario.init(39, 10, 3, 3, jbeau::state::PLAYER_SYMBOL);
	state.score = 0;
	
	switch(lvl) {
		case 1:
		get_new_brick(state)->init(20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(60, 15, 40, 10, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(100, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);
		
		get_new_brick(state)->init(30, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		get_new_brick(state)->init(50, 10, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		get_new_brick(state)->init(60, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		get_new_brick(state)->init(70, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		get_new_brick(state)->init(75, 5, 5, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		get_new_brick(state)->init(80, 5, 5, 3, jbeau::state::BONUS_BRICK_SYMBOL);
		get_new_brick(state)->init(85, 5, 10, 3, jbeau::state::EMPTY_BRICK_SYMBOL);
		
		get_new_moving(state)->init(25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		break;
		
		case 2:
		get_new_brick(state)->init(20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(60, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(80, 20, 20, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(120, 15, 10, 10, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(150, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(210, 15, 10, 10, jbeau::state::FINISH_SYMBOL);

		get_new_moving(state)->init(25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(65, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(160, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(175, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		break;
		
		case 3:
		get_new_brick(state)->init(20, 20, 40, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(80, 20, 15, 5, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(120, 15, 15, 10, jbeau::state::BRICK_SYMBOL);
		get_new_brick(state)->init(160, 10, 15, 15, jbeau::state::FINISH_SYMBOL);

		get_new_moving(state)->init(25, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(50, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(80, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(90, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(120, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		get_new_moving(state)->init(130, 10, 3, 2, jbeau::state::ENEMY_SYMBOL);
		
		lvl = 1;
		break;
	}
	
	state.max_lvl = 3;
}