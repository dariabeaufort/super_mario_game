#include "mario.hpp"

#include "collision.hpp"
#include "game_state.hpp"

jbeau::mario::Mario::Mario() {
    alive = true;
	reached_finish = false;

    width = 3;
    height = 3;
    c_type = jbeau::state::PLAYER_SYMBOL;

    spawn();
}

void jbeau::mario::Mario::spawn() {
    x = 39;
    y = 10;
    vert_speed = 0;
    horiz_speed = 0;
	
    is_fly = true;
    alive = true;
	reached_finish = false;
}

void jbeau::mario::Mario::jump() {
    vert_speed = jbeau::state::JUMP_SPEED;
}

void jbeau::mario::Mario::death() {
    alive = false;
}

void jbeau::mario::Mario::vert_movement(
    jbeau::state::GameState& state
) {
    is_fly = true;
    reached_finish = false;

    vert_speed += jbeau::state::GRAVITY;

    set_pos(x, y + vert_speed);

    for (int i = 0; i < state.brick_length; i++) {
        if (jbeau::collision::is_collision(*this, state.brick[i])) {

            if (vert_speed > 0) {
                is_fly = false;
            }

            if ((state.brick[i].c_type == jbeau::state::BONUS_BRICK_SYMBOL)
                && (vert_speed < 0)) {

                state.brick[i].c_type = jbeau::state::EMPTY_BRICK_SYMBOL;

				jbeau::state::get_new_moving(state)->init(
					state.brick[i].x, state.brick[i].y - 3, 3, 2,
					jbeau::state::MONEY_SYMBOL
				);

                state.moving[state.moving_length - 1].vert_speed =
                    jbeau::state::MOVING_VERT_SPEED;
            }

            y -= vert_speed;
            vert_speed = 0;

            if (state.brick[i].c_type == jbeau::state::FINISH_SYMBOL) {
                reached_finish = true;
            }

            break;
        }
    }
}

bool jbeau::mario::Mario::get_alive() const {
    return alive;
}

bool jbeau::mario::Mario::get_reached_finish() const {
    return reached_finish;
}