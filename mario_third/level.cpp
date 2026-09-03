#include "level.hpp"

#include <cstdlib>
#include <windows.h>

using namespace jbeau;

level::Level::Level() {
    level = 1;

    bricks = nullptr;
    enemies = nullptr;
    money = nullptr;

    brick_count = 0;
    enemy_count = 0;
    money_count = 0;
}

level::Level::~Level() {
    clear();
}

void level::Level::clear() {
    delete[] bricks;
    delete[] enemies;
    delete[] money;

    bricks = nullptr;
    enemies = nullptr;
    money = nullptr;

    brick_count = 0;
    enemy_count = 0;
    money_count = 0;
}

void level::Level::create_level(int level_number) {
    system("color DF");

    clear();

    level = level_number;

    int i = 0;

    switch (level) {
        case 1:
            brick_count = 13;
            bricks = new brick::Brick[brick_count];

            i = 0;
            bricks[i++].spawn(20, 20, 40, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(60, 15, 40, 10, brick::BrickType::BRICK);
            bricks[i++].spawn(100, 20, 20, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(120, 15, 10, 10, brick::BrickType::BRICK);
            bricks[i++].spawn(150, 20, 40, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(210, 15, 10, 10, brick::BrickType::FINISH);

            bricks[i++].spawn(30, 10, 5, 3, brick::BrickType::BONUS);
            bricks[i++].spawn(50, 10, 5, 3, brick::BrickType::BONUS);
            bricks[i++].spawn(60, 5, 10, 3, brick::BrickType::EMPTY);
            bricks[i++].spawn(70, 5, 5, 3, brick::BrickType::BONUS);
            bricks[i++].spawn(75, 5, 5, 3, brick::BrickType::EMPTY);
            bricks[i++].spawn(80, 5, 5, 3, brick::BrickType::BONUS);
            bricks[i++].spawn(85, 5, 10, 3, brick::BrickType::EMPTY);

            enemy_count = 2;
            enemies = new enemy::Enemy[enemy_count];

            i = 0;
            enemies[i++].spawn(25, 10);
            enemies[i++].spawn(80, 10);
            break;

        case 2:
            brick_count = 6;
            bricks = new brick::Brick[brick_count];

            i = 0;
            bricks[i++].spawn(20, 20, 40, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(60, 15, 10, 10, brick::BrickType::BRICK);
            bricks[i++].spawn(80, 20, 20, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(120, 15, 10, 10, brick::BrickType::BRICK);
            bricks[i++].spawn(150, 20, 40, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(210, 15, 10, 10, brick::BrickType::FINISH);

            enemy_count = 6;
            enemies = new enemy::Enemy[enemy_count];

            i = 0;
            enemies[i++].spawn(25, 10);
            enemies[i++].spawn(80, 10);
            enemies[i++].spawn(65, 10);
            enemies[i++].spawn(120, 10);
            enemies[i++].spawn(160, 10);
            enemies[i++].spawn(175, 10);
            break;

        case 3:
            brick_count = 4;
            bricks = new brick::Brick[brick_count];

            i = 0;
            bricks[i++].spawn(20, 20, 40, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(80, 20, 15, 5, brick::BrickType::BRICK);
            bricks[i++].spawn(120, 15, 15, 10, brick::BrickType::BRICK);
            bricks[i++].spawn(160, 10, 15, 15, brick::BrickType::FINISH);

            enemy_count = 6;
            enemies = new enemy::Enemy[enemy_count];

            i = 0;
            enemies[i++].spawn(25, 10);
            enemies[i++].spawn(50, 10);
            enemies[i++].spawn(80, 10);
            enemies[i++].spawn(90, 10);
            enemies[i++].spawn(120, 10);
            enemies[i++].spawn(130, 10);
            break;

        default:
            level = 1;
            break;
    }
}

void level::Level::spawn_money(float x_pos, float y_pos) {
    money_count++;

    money::Money *new_money = new money::Money[money_count];
    for (int i = 0; i < money_count - 1; i++) {
        new_money[i] = money[i];
    }
    delete[] money;
    money = new_money;

    money[money_count - 1].spawn(x_pos, y_pos);
}

void level::Level::remove_enemy(int index) {
    if (index < 0 || index >= enemy_count) {
        return;
    }

    enemy_count--;
    enemies[index] = enemies[enemy_count];

    enemy::Enemy *new_enemies = nullptr;

    if (enemy_count > 0) {
        new_enemies = new enemy::Enemy[enemy_count];
        for (int i = 0; i < enemy_count; i++) {
            new_enemies[i] = enemies[i];
        }
    }

    delete[] enemies;
    enemies = new_enemies;
}

void level::Level::remove_money(int index) {
    if (index < 0 || index >= money_count) {
        return;
    }

    money_count--;
    money[index] = money[money_count];

    money::Money *new_money = nullptr;

    if (money_count > 0) {
        new_money = new money::Money[money_count];
        for (int i = 0; i < money_count; i++) {
            new_money[i] = money[i];
        }
    }

    delete[] money;
    money = new_money;
}

brick::Brick *level::Level::get_bricks() {
    return bricks;
}

enemy::Enemy *level::Level::get_enemies() {
    return enemies;
}

money::Money *level::Level::get_money() {
    return money;
}

int level::Level::get_brick_count() const {
    return brick_count;
}

int level::Level::get_enemy_count() const {
    return enemy_count;
}

int level::Level::get_money_count() const {
    return money_count;
}

int level::Level::get_level() const {
    return level;
}