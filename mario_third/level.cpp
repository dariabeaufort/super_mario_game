#include <stdlib.h>

#include <windows.h>

#include "game_state.hpp"
#include "object.hpp"

#include "level.hpp"

void jbeau::level::create_level(jbeau::state::GameState &state, int lvl) {
	system("color DF");
	
	delete[] state.brick;
	state.brick = nullptr;
	state.brick_length = 0;
	
	delete[] state.enemy;
	state.enemy = nullptr;
	state.enemy_length = 0;

	delete[] state.money;
	state.money = nullptr;
	state.money_length = 0;
	
	state.mario.spawn();
	state.score = 0;
	
	switch(lvl) {
		case 1:
		jbeau::state::get_new_brick(state)->spawn(20, 20, 40, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(60, 15, 40, 10, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(100, 20, 20, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(120, 15, 10, 10, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(150, 20, 40, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(210, 15, 10, 10, jbeau::brick::BrickType::FINISH);
		
		jbeau::state::get_new_brick(state)->spawn(30, 10, 5, 3, jbeau::brick::BrickType::BONUS);
		jbeau::state::get_new_brick(state)->spawn(50, 10, 5, 3, jbeau::brick::BrickType::BONUS);
		jbeau::state::get_new_brick(state)->spawn(60, 5, 10, 3, jbeau::brick::BrickType::EMPTY);
		jbeau::state::get_new_brick(state)->spawn(70, 5, 5, 3, jbeau::brick::BrickType::BONUS);
		jbeau::state::get_new_brick(state)->spawn(75, 5, 5, 3, jbeau::brick::BrickType::EMPTY);
		jbeau::state::get_new_brick(state)->spawn(80, 5, 5, 3, jbeau::brick::BrickType::BONUS);
		jbeau::state::get_new_brick(state)->spawn(85, 5, 10, 3, jbeau::brick::BrickType::EMPTY);
		
		jbeau::state::get_new_enemy(state)->spawn(25, 10);
		jbeau::state::get_new_enemy(state)->spawn(80, 10);
		break;
		
		case 2:
		jbeau::state::get_new_brick(state)->spawn(20, 20, 40, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(60, 15, 10, 10, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(80, 20, 20, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(120, 15, 10, 10, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(150, 20, 40, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(210, 15, 10, 10, jbeau::brick::BrickType::FINISH);

		jbeau::state::get_new_enemy(state)->spawn(25, 10);
		jbeau::state::get_new_enemy(state)->spawn(80, 10);
		jbeau::state::get_new_enemy(state)->spawn(65, 10);
		jbeau::state::get_new_enemy(state)->spawn(120, 10);
		jbeau::state::get_new_enemy(state)->spawn(160, 10);
		jbeau::state::get_new_enemy(state)->spawn(175, 10);
		break;
		
		case 3:
		jbeau::state::get_new_brick(state)->spawn(20, 20, 40, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(80, 20, 15, 5, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(120, 15, 15, 10, jbeau::brick::BrickType::BRICK);
		jbeau::state::get_new_brick(state)->spawn(160, 10, 15, 15, jbeau::brick::BrickType::FINISH);

		jbeau::state::get_new_enemy(state)->spawn(25, 10);
		jbeau::state::get_new_enemy(state)->spawn(50, 10);
		jbeau::state::get_new_enemy(state)->spawn(80, 10);
		jbeau::state::get_new_enemy(state)->spawn(90, 10);
		jbeau::state::get_new_enemy(state)->spawn(120, 10);
		jbeau::state::get_new_enemy(state)->spawn(130, 10);
		
		lvl = 1;
		break;
	}
	
	state.max_lvl = 3;
}