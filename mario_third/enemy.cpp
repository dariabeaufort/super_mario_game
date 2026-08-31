#include "enemy.hpp"

#include "game_state.hpp"
#include "collision.hpp"

jbeau::enemy::Enemy::Enemy() {
    x = -1000;
    y = -1000;

    width = 3;
    height = 2;

    vert_speed = 0;
    horiz_speed = jbeau::state::GROUND_SPEED;

    is_fly = true;

    c_type = jbeau::state::ENEMY_SYMBOL;
}

void jbeau::enemy::Enemy::spawn(float x_pos, float y_pos) {
    x = x_pos;
    y = y_pos;

    vert_speed = 0;
    horiz_speed = jbeau::state::GROUND_SPEED;

    is_fly = true;
}

void jbeau::enemy::Enemy::vert_movement(jbeau::brick::Brick* bricks,
								 int brick_length) {
    is_fly = true;

    vert_speed += jbeau::state::GRAVITY;

    set_pos(x, y + vert_speed);

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

void jbeau::enemy::Enemy::horizon_movement(jbeau::brick::Brick* bricks,
									int brick_length) {
    x += horiz_speed;

    for (int i = 0; i < brick_length; i++) {
        if (jbeau::collision::is_collision(*this, bricks[i])) {
            x -= horiz_speed;
            horiz_speed = -horiz_speed;
            return;
        }
    }

    Enemy temp = *this;
    temp.vert_movement(bricks, brick_length);

    if (temp.is_fly) {
        x -= horiz_speed;
        horiz_speed = -horiz_speed;
    }
}