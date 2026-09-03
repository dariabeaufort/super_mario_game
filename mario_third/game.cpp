#include "game.hpp"

#include <cstdlib>
#include <windows.h>

#include "collision.hpp"
#include "level.hpp"
#include "render.hpp"

using namespace jbeau;

game::Game::Game() {
    is_running = false;

    state.level = 1;
    state.score = 0;
    state.max_lvl = 3;
}

game::Game::~Game() {
	is_running = false;
}

void game::Game::init() {
    is_running = true;

	state.level = 1;
	state.score = 0;

    level.create_level(state.level);
}

void game::Game::run() {
    while (is_running) {
        input();
        update();
        show();

        Sleep(state::FRAME_SLEEP_MS);
    }
}

void game::Game::input() {
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

    if (state.mario.y > state::MAP_HEIGHT) {
        state.mario.death();
    }
}

void game::Game::horizon_move_map(float dx) {
    state.mario.x -= dx;

    for (int i = 0; i < level.get_brick_count(); i++) {
        if (collision::is_collision(state.mario, level.get_bricks()[i])) {
            state.mario.x += dx;
            return;
        }
    }

    state.mario.x += dx;

    for (int i = 0; i < level.get_brick_count(); i++) {
        level.get_bricks()[i].x += dx;
    }

    for (int i = 0; i < level.get_enemy_count(); i++) {
        level.get_enemies()[i].x += dx;
    }

    for (int i = 0; i < level.get_money_count(); i++) {
        level.get_money()[i].x += dx;
    }
}

void game::Game::update() {
    state.mario.vert_movement(level);

    if (state.mario.get_reached_finish()) {
        next_level();
        return;
    }

    for (int i = 0; i < level.get_enemy_count(); i++) {
        level.get_enemies()[i].vert_movement(level.get_bricks(), level.get_brick_count());
        level.get_enemies()[i].horizon_movement(level.get_bricks(), level.get_brick_count());
    }

    for (int i = 0; i < level.get_money_count(); i++) {
        level.get_money()[i].vert_movement(level.get_bricks(), level.get_brick_count());
        level.get_money()[i].horizon_movement(level.get_bricks(), level.get_brick_count());
    }

    handle_collisions();

    if (!state.mario.get_alive()) {
        player_dead();
    }
}

void game::Game::handle_collisions() {
    for (int i = 0; i < level.get_enemy_count(); i++) {
        if (state.mario.up_enemy_collision(level.get_enemies()[i])) {
            state.score += state::ENEMY_SCORE;
            level.remove_enemy(i);
            i--;
            continue;
        }

        if (state.mario.enemy_collision(level.get_enemies()[i])) {
            state.mario.death();
            return;
        }
    }

    for (int i = 0; i < level.get_money_count(); i++) {
        if (state.mario.money_collision(level.get_money()[i])) {
            state.score += state::MONEY_SCORE;
            level.remove_money(i);
            i--;
            continue;
        }
    }
}

void game::Game::player_dead() {
    system("color 4F");
    Sleep(state::DEAD_SCREEN_TIME_MS);

    level.create_level(state.level);
	state.mario.spawn();
	state.score = 0;
}

void game::Game::next_level() {
    state.level++;

    if (state.level > state.max_lvl) {
        state.level = 1;
    }

    system("color 2F");
    Sleep(state::LVL_SWITCH_TIME_MS);

    level.create_level(state.level);
	state.mario.spawn();
	state.score = 0;
}

void game::Game::show() {
    renderer.clear_map();

    for (int i = 0; i < level.get_brick_count(); i++) {
        renderer.put_object_on_map(level.get_bricks()[i]);
    }

    for (int i = 0; i < level.get_enemy_count(); i++) {
        renderer.put_object_on_map(level.get_enemies()[i]);
    }

    for (int i = 0; i < level.get_money_count(); i++) {
        renderer.put_object_on_map(level.get_money()[i]);
    }

    renderer.put_object_on_map(state.mario);
    renderer.put_score_on_map(state.score);
	
    renderer.set_cur(0, 0);
    renderer.show_map();
}

void game::Game::stop() {
    is_running = false;
}