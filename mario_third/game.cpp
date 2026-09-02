#include "game.hpp"

#include <cstdlib>
#include <windows.h>

#include "collision.hpp"
#include "level.hpp"
#include "render.hpp"

jbeau::game::Game::Game() {
    is_running = false;

    state.level = 1;
    state.score = 0;
    state.max_lvl = 3;
}

jbeau::game::Game::~Game() {
    delete[] state.brick;
    delete[] state.enemy;
    delete[] state.money;

    state.brick = nullptr;
    state.enemy = nullptr;
    state.money = nullptr;
}

void jbeau::game::Game::init() {
    is_running = true;

    jbeau::level::create_level(state, state.level);
}

void jbeau::game::Game::run() {
    while (is_running) {
        input();
        update();
        show();

        Sleep(jbeau::state::FRAME_SLEEP_MS);
    }
}

void jbeau::game::Game::input() {
    if (GetKeyState(VK_ESCAPE) < 0) {
        stop();
        return;
    }

    if ((state.mario.is_fly == false) && (GetKeyState(VK_SPACE) < 0)) {
        state.mario.jump();
    }

    if (GetKeyState('A') < 0) {
        horizon_move_map(1);
    }

    if (GetKeyState('D') < 0) {
        horizon_move_map(-1);
    }

    if (state.mario.y > jbeau::state::MAP_HEIGHT) {
        state.mario.death();
    }
}

void jbeau::game::Game::horizon_move_map(float dx) {
    state.mario.x -= dx;

    for (int i = 0; i < state.brick_length; i++) {
        if (jbeau::collision::is_collision(state.mario, state.brick[i])) {
            state.mario.x += dx;
            return;
        }
    }

    state.mario.x += dx;

    for (int i = 0; i < state.brick_length; i++) {
        state.brick[i].x += dx;
    }

    for (int i = 0; i < state.enemy_length; i++) {
        state.enemy[i].x += dx;
    }

    for (int i = 0; i < state.money_length; i++) {
        state.money[i].x += dx;
    }
}

void jbeau::game::Game::update() {
    state.mario.vert_movement(state);

    if (state.mario.get_reached_finish()) {
        next_level();
        return;
    }

    for (int i = 0; i < state.enemy_length; i++) {
        state.enemy[i].vert_movement(state.brick, state.brick_length);
        state.enemy[i].horizon_movement(state.brick, state.brick_length);
    }

    for (int i = 0; i < state.money_length; i++) {
        state.money[i].vert_movement(state.brick, state.brick_length);
        state.money[i].horizon_movement(state.brick, state.brick_length);
    }

    handle_collisions();

    if (!state.mario.get_alive()) {
        player_dead();
    }
}

void jbeau::game::Game::handle_collisions() {
    for (int i = 0; i < state.enemy_length; i++) {
        if (state.mario.up_enemy_collision(state.enemy[i])) {
            state.score += jbeau::state::ENEMY_SCORE;
            jbeau::state::delete_enemy(state, i);
            i--;
            continue;
        }

        if (state.mario.enemy_collision(state.enemy[i])) {
            state.mario.death();
            return;
        }
    }

    for (int i = 0; i < state.money_length; i++) {
        if (state.mario.money_collision(state.money[i])) {
            state.score += jbeau::state::MONEY_SCORE;
            jbeau::state::delete_money(state, i);
            i--;
            continue;
        }
    }
}

void jbeau::game::Game::player_dead() {
    system("color 4F");
    Sleep(jbeau::state::DEAD_SCREEN_TIME_MS);

    jbeau::level::create_level(state, state.level);
}

void jbeau::game::Game::next_level() {
    state.level++;

    if (state.level > state.max_lvl) {
        state.level = 1;
    }

    system("color 2F");
    Sleep(jbeau::state::LVL_SWITCH_TIME_MS);

    jbeau::level::create_level(state, state.level);
}

void jbeau::game::Game::show() {
    jbeau::render::clear_map(state);

    for (int i = 0; i < state.brick_length; i++) {
        jbeau::render::put_object_on_map(state, state.brick[i]);
    }

    for (int i = 0; i < state.enemy_length; i++) {
        jbeau::render::put_object_on_map(state,state.enemy[i]);
    }

    for (int i = 0; i < state.money_length; i++) {
        jbeau::render::put_object_on_map(state, state.money[i]);
    }

    jbeau::render::put_object_on_map(state, state.mario);

    jbeau::render::put_score_on_map(state);
    jbeau::render::set_cur(0, 0);

    jbeau::render::show_map(state);
}

void jbeau::game::Game::stop() {
    is_running = false;
}