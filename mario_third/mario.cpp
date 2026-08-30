#include "mario.hpp"
#include "game_state.hpp"

jbeau::mario::Mario::Mario() {
    alive = true;

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
}

void jbeau::mario::Mario::jump() {
    vert_speed = jbeau::state::JUMP_SPEED;
}

void jbeau::mario::Mario::death() {
    alive = false;
}

bool jbeau::mario::Mario::get_is_alive() const {
    return alive;
}