#include <cstdlib>

#include "game_state.hpp"


jbeau::brick::Brick *jbeau::state::get_new_brick(GameState &state) {
    state.brick_length++;

    jbeau::brick::Brick *new_brick = new jbeau::brick::Brick[state.brick_length];

    for (int i = 0; i < state.brick_length - 1; i++) {
        new_brick[i] = state.brick[i];
    }

    delete[] state.brick;
    state.brick = new_brick;

    return &state.brick[state.brick_length - 1];
}


jbeau::enemy::Enemy *jbeau::state::get_new_enemy(GameState &state) {
    state.enemy_length++;

    jbeau::enemy::Enemy *new_enemy = new jbeau::enemy::Enemy[state.enemy_length];

    for (int i = 0; i < state.enemy_length - 1; i++) {
        new_enemy[i] = state.enemy[i];
    }

    delete[] state.enemy;
    state.enemy = new_enemy;

    return &state.enemy[state.enemy_length - 1];
}


void jbeau::state::delete_enemy(GameState &state, int i) {
    state.enemy_length--;

    state.enemy[i] = state.enemy[state.enemy_length];

    jbeau::enemy::Enemy *new_enemy = new jbeau::enemy::Enemy[state.enemy_length];

    for (int j = 0; j < state.enemy_length; j++) {
        new_enemy[j] = state.enemy[j];
    }

    delete[] state.enemy;
    state.enemy = new_enemy;
}

jbeau::money::Money *jbeau::state::get_new_money(GameState &state) {
    state.money_length++;

    jbeau::money::Money *new_money = new jbeau::money::Money[state.money_length];

    for (int i = 0; i < state.money_length - 1; i++) {
        new_money[i] = state.money[i];
    }

    delete[] state.money;
    state.money = new_money;

    return &state.money[state.money_length - 1];
}

void jbeau::state::delete_money(GameState &state, int i) {
    state.money_length--;

    state.money[i] = state.money[state.money_length];

    jbeau::money::Money *new_money = new jbeau::money::Money[state.money_length];

    for (int j = 0; j < state.money_length; j++) {
        new_money[j] = state.money[j];
    }

    delete[] state.money;
    state.money = new_money;
}