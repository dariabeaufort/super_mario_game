#include "mario.hpp"

#include "collision.hpp"
#include "game_state.hpp"
#include "level.hpp"

using namespace jbeau;

mario::Mario::Mario() {
    alive = true;
    reached_finish = false;

    width = 3;
    height = 3;
    c_type = state::PLAYER_SYMBOL;

    spawn();
}

void mario::Mario::spawn() {
    x = 39;
    y = 10;

    vert_speed = 0;
    horiz_speed = 0;

    is_fly = true;
    alive = true;

    reached_finish = false;
}

void mario::Mario::jump() {
    vert_speed = state::JUMP_SPEED;
    is_fly = true;
}

void mario::Mario::death() {
    alive = false;
}

void mario::Mario::gravity() {
    vert_speed += state::GRAVITY;
}

void mario::Mario::vert_movement(level::Level& level) {
    is_fly = true;

    gravity();

    reached_finish = false;

    set_pos(x, y + vert_speed);

    for (int i = 0; i < level.get_brick_count(); i++) {
        if (collision::is_collision(*this, level.get_bricks()[i])) {

            if (vert_speed > 0) {
                is_fly = false;
            }

            if (level.get_bricks()[i].get_type() == brick::BrickType::BONUS
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

bool mario::Mario::enemy_collision(const enemy::Enemy& enemy) const {
    return collision::is_collision(*this, enemy);
}

bool mario::Mario::up_enemy_collision(const enemy::Enemy& enemy) const {
    if (!collision::is_collision(*this, enemy)) {
        return false;
    }

    return is_fly && vert_speed > 0 
		   && y + height < enemy.y + enemy.height * 0.5f;
}

bool mario::Mario::money_collision(const money::Money& money) const {
    return collision::is_collision(*this, money);
}

bool mario::Mario::get_alive() const {
    return alive;
}

bool mario::Mario::get_reached_finish() const {
    return reached_finish;
}