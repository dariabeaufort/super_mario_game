#pragma once

#include "brick.hpp"
#include "enemy.hpp"
#include "money.hpp"

namespace jbeau {
    namespace level {
        class Level {
        private:
            int level;

            jbeau::brick::Brick *bricks;
            jbeau::enemy::Enemy *enemies;
            jbeau::money::Money *money;

            int brick_count;
            int enemy_count;
            int money_count;

            void clear();

        public:
            Level();
            ~Level();
			Level(const Level&) = delete;
			Level& operator=(const Level&) = delete;

            void create_level(int level_number);

            void spawn_money(float x_pos, float y_pos);

            void remove_enemy(int index);
            void remove_money(int index);

            jbeau::brick::Brick *get_bricks();
            jbeau::enemy::Enemy *get_enemies();
            jbeau::money::Money *get_money();

            int get_brick_count() const;
            int get_enemy_count() const;
            int get_money_count() const;
            int get_level() const;
        };
    }
}