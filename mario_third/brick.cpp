#include "brick.hpp"

jbeau::brick::Brick::Brick() {
    x = -1000;
    y = -1000;

    width = 0;
    height = 0;

    vert_speed = 0;
    horiz_speed = 0;

    is_fly = false;

    c_type = '#';

    brick_type = BrickType::BRICK;
    was_hit = false;
}

void jbeau::brick::Brick::spawn(
    float x_pos,
    float y_pos,
    float obj_width,
    float obj_height,
    BrickType type
) {
    x = x_pos;
    y = y_pos;

    width = obj_width;
    height = obj_height;

    brick_type = type;
    was_hit = false;

    switch (brick_type) {
        case BrickType::BRICK:
            c_type = '#';
            break;

        case BrickType::BONUS:
            c_type = '?';
            break;

        case BrickType::EMPTY:
            c_type = '-';
            break;

        case BrickType::FINISH:
            c_type = '+';
            break;
    }
}

void jbeau::brick::Brick::hit() {
    if (brick_type == BrickType::BONUS && !was_hit) {
        brick_type = BrickType::EMPTY;
        c_type = '-';
        was_hit = true;
    }
}

jbeau::brick::BrickType jbeau::brick::Brick::get_type() const {
    return brick_type;
}

bool jbeau::brick::Brick::is_finish() const {
    return brick_type == BrickType::FINISH;
}