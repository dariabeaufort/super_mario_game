#include "game_state.hpp"
#include "movement.hpp"

#include "collision.hpp"

bool jbeau::collision::is_collision(
	const jbeau::object::Object &obj_1,
	const jbeau::object::Object &obj_2
) {
	return ((obj_1.x + obj_1.width) > obj_2.x)
		   && (obj_1.x < (obj_2.x + obj_2.width))
		   && ((obj_1.y + obj_1.height) > obj_2.y)
		   && (obj_1.y < (obj_2.y + obj_2.height));
}

void jbeau::collision::mario_collision(jbeau::state::GameState &state) {
	for (int i = 0; i < state.moving_length; i++) {
		if (jbeau::collision::is_collision(state.mario, state.moving[i])) {
			if (state.moving[i].c_type == jbeau::state::ENEMY_SYMBOL) {
				if ((state.mario.is_fly == true) 
					&& (state.mario.vert_speed > 0) 
					&& (state.mario.y + state.mario.height 
					< state.moving[i].y + state.moving[i].height * 0.5)) {
					state.score += jbeau::state::ENEMY_SCORE;
					jbeau::state::delete_moving(state, i);
					i--;
					continue;
				} else {
					jbeau::movement::player_dead(state);
				}
			}
			
			if (state.moving[i].c_type == jbeau::state::MONEY_SYMBOL) {
				state.score += jbeau::state::MONEY_SCORE;
				jbeau::state::delete_moving(state, i);
				i--;
				continue;
			}
		}
	}
}