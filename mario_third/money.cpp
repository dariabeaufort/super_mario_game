#include "money.hpp"

#include "collision.hpp"
#include "game_state.hpp"

using namespace jbeau;

money::Money::Money() {
	x = -1000;
    y = -1000;

    width = 3;
    height = 2;

    vert_speed = -0.3f;
    horiz_speed = 0.5f;

    is_fly = true;
    c_type = state::MONEY_SYMBOL;
}

void money::Money::spawn(float x_pos, float y_pos) {
    x = x_pos;
    y = y_pos - 3;

    vert_speed = state::MOVING_VERT_SPEED;
    horiz_speed = state::GROUND_SPEED;

    is_fly = true;
}

void money::Money::vert_movement(brick::Brick* bricks, 
										int brick_length) {
    is_fly = true;

    vert_speed += state::GRAVITY;
    y += vert_speed;

    for (int i = 0; i < brick_length; i++) {
        if (collision::is_collision(*this, bricks[i])) {
            if (vert_speed > 0) {
                is_fly = false;
            }

            y -= vert_speed;
            vert_speed = 0;

            break;
        }
    }
}

void money::Money::horizon_movement(brick::Brick* bricks,
										   int brick_length) {
    x += horiz_speed;

    for (int i = 0; i < brick_length; i++) {
        if (collision::is_collision(*this, bricks[i])) {
            x -= horiz_speed;
            horiz_speed = -horiz_speed;
            return;
        }
    }
}