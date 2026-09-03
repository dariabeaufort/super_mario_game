#include "mario.hpp"

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"

jbeau::mario::Mario::Mario() {
    alive = true;
    prev_y = 10;
    hit_brick_from_below = -1;
    reached_finish = false;

    width = 3;
    height = 3;
    c_type = jbeau::state::PLAYER_SYMBOL;

    spawn();
}

void jbeau::mario::Mario::spawn() {
    prev_y = y;

    x = 39;
    y = 10;

    vert_speed = 0;
    horiz_speed = 0;

    is_fly = true;
    alive = true;

    hit_brick_from_below = -1;
    reached_finish = false;
}

void jbeau::mario::Mario::jump() {
    vert_speed = jbeau::state::JUMP_SPEED;
    is_fly = true;
}

void jbeau::mario::Mario::death() {
    alive = false;
}

void jbeau::mario::Mario::gravity() {
    vert_speed += jbeau::state::GRAVITY;
}

void jbeau::mario::Mario::vert_movement(jbeau::level::Level& level) {
    prev_y = y;
    is_fly = true;

    gravity();

    hit_brick_from_below = -1;
    reached_finish = false;

    set_pos(x, y + vert_speed);

    for (int i = 0; i < level.get_brick_count(); i++) {
        if (jbeau::collision::is_collision(*this, level.get_bricks()[i])) {

            if (vert_speed > 0) {
                is_fly = false;
            } else if (vert_speed < 0) {
                hit_brick_from_below = i;
            }

            if (level.get_bricks()[i].get_type() == jbeau::brick::BrickType::BONUS
                && vert_speed < 0) {

                if (!level.get_bricks()[i].get_was_hit()) {
                    level.get_bricks()[i].hit();

                    level.spawn_money(level.get_bricks()[i].x, level.get_bricks()[i].y);
                }
            }

            y -= vert_speed;
            vert_speed = 0;

            if (level.get_bricks()[i].is_finish()) {
                reached_finish = true;
            }

            break;
        }
    }
}

bool jbeau::mario::Mario::enemy_collision(const jbeau::enemy::Enemy& enemy) const {
    return jbeau::collision::is_collision(*this, enemy);
}

bool jbeau::mario::Mario::up_enemy_collision(const jbeau::enemy::Enemy& enemy) const {
    if (!jbeau::collision::is_collision(*this, enemy)) {
        return false;
    }

    return is_fly && vert_speed > 0 
		   && y + height < enemy.y + enemy.height * 0.5f;
}

bool jbeau::mario::Mario::money_collision(const jbeau::money::Money& money) const {
    return jbeau::collision::is_collision(*this, money);
}

bool jbeau::mario::Mario::get_alive() const {
    return alive;
}

bool jbeau::mario::Mario::get_reached_finish() const {
    return reached_finish;
}

float jbeau::mario::Mario::get_prev_y() const {
    return prev_y;
}

int jbeau::mario::Mario::get_hit_brick_from_below() const {
    return hit_brick_from_below;
}
