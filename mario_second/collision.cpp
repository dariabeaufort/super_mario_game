#include "collision.hpp"

#include "game_state.hpp"
#include "movement.hpp"

using jbeau::state::mario;
using jbeau::state::moving;
using jbeau::state::moving_length;
using jbeau::state::score;

using jbeau::state::delete_moving;

using jbeau::movement::player_dead;

// temporary dependencies (to be refactored later)
static const int ENEMY_SCORE = 50;
static const int MONEY_SCORE = 100;

static const char ENEMY_SYMBOL = 'o';
static const char MONEY_SYMBOL = '$';

//void player_dead();

bool jbeau::collision::is_collision(
	jbeau::object::Object obj_1,
	jbeau::object::Object obj_2
) {
	return ((obj_1.x + obj_1.width) > obj_2.x)
		   && (obj_1.x < (obj_2.x + obj_2.width))
		   && ((obj_1.y + obj_1.height) > obj_2.y)
		   && (obj_1.y < (obj_2.y + obj_2.height));
}

void jbeau::collision::mario_collision() {
	for (int i = 0; i < moving_length; i++) {
		if (jbeau::collision::is_collision(mario, moving[i])) {
			if (moving[i].c_type == ENEMY_SYMBOL) {
				if ((mario.is_fly == true) 
					&& (mario.vert_speed > 0) 
					&& (mario.y + mario.height 
					< moving[i].y + moving[i].height * 0.5)) {
					score += ENEMY_SCORE;
					delete_moving(i);
					i--;
					continue;
				} else {
					player_dead();
				}
			}
			
			if (moving[i].c_type == MONEY_SYMBOL) {
				score += MONEY_SCORE;
				delete_moving(i);
				i--;
				continue;
			}
		}
	}
}