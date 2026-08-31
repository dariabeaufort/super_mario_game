#include "money.hpp"

#include "game_state.hpp"
#include "collision.hpp"

jbeau::money::Money::Money() {
	x = -1000;
    y = -1000;

    width = 3;
    height = 2;

    vert_speed = -0.3f;
    horiz_speed = 0.5f;

    is_fly = true;
    c_type = jbeau::state::MONEY_SYMBOL;
}

void jbeau::money::Money::spawn(float x_pos, float y_pos) {
    x = x_pos;
    y = y_pos - 3;

    vert_speed = jbeau::state::MOVING_VERT_SPEED;
    horiz_speed = jbeau::state::GROUND_SPEED;

    is_fly = true;
}

void jbeau::money::Money::vert_movement(jbeau::brick::Brick* bricks, 
										int brick_length) {
    is_fly = true;

    vert_speed += jbeau::state::GRAVITY;
    y += vert_speed;

    for (int i = 0; i < brick_length; i++) {
        if (jbeau::collision::is_collision(*this, bricks[i])) {
            if (vert_speed > 0) {
                is_fly = false;
            }

            y -= vert_speed;
            vert_speed = 0;

            break;
        }
    }
}

void jbeau::money::Money::horizon_movement(jbeau::brick::Brick* bricks,
										   int brick_length) {
    x += horiz_speed;

    for (int i = 0; i < brick_length; i++) {
        if (jbeau::collision::is_collision(*this, bricks[i])) {
            x -= horiz_speed;
            horiz_speed = -horiz_speed;
            return;
        }
    }
}