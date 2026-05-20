#include "game_state.hpp"
#include "movement.hpp"

#include "collision.hpp"

using jbeau::state::mario;
using jbeau::state::moving;

bool jbeau::collision::is_collision(
	const jbeau::object::Object &obj_1,
	const jbeau::object::Object &obj_2
) {
	return ((obj_1.x + obj_1.width) > obj_2.x)
		   && (obj_1.x < (obj_2.x + obj_2.width))
		   && ((obj_1.y + obj_1.height) > obj_2.y)
		   && (obj_1.y < (obj_2.y + obj_2.height));
}

void jbeau::collision::mario_collision() {
	for (int i = 0; i < jbeau::state::moving_length; i++) {
		if (jbeau::collision::is_collision(mario, moving[i])) {
			if (moving[i].c_type == jbeau::state::ENEMY_SYMBOL) {
				if ((mario.is_fly == true) 
					&& (mario.vert_speed > 0) 
					&& (mario.y + mario.height 
					< moving[i].y + moving[i].height * 0.5)) {
					jbeau::state::score += jbeau::state::ENEMY_SCORE;
					jbeau::state::delete_moving(i);
					i--;
					continue;
				} else {
					jbeau::movement::player_dead();
				}
			}
			
			if (moving[i].c_type == jbeau::state::MONEY_SYMBOL) {
				jbeau::state::score += jbeau::state::MONEY_SCORE;
				jbeau::state::delete_moving(i);
				i--;
				continue;
			}
		}
	}
}