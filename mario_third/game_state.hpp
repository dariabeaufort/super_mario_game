#pragma once

#include "brick.hpp"
#include "mario.hpp"
#include "object.hpp"

#include "enemy.hpp"
#include "money.hpp"

namespace jbeau {
	namespace state {
		static const int MAP_WIDTH = 80;
		static const int MAP_HEIGHT = 25;
		
		static const float GRAVITY = 0.05f;
		static const float JUMP_SPEED = -1.0f;
		static const float GROUND_SPEED = 0.5f;
		static const float MOVING_VERT_SPEED = -0.3f;

		static const int DEAD_SCREEN_TIME_MS = 500;
		static const int LVL_SWITCH_TIME_MS = 500;
		static const int FRAME_SLEEP_MS = 10;

		static const int SCORE_TEXT_X = 5;
		static const int SCORE_TEXT_Y = 1;

		static const int ENEMY_SCORE = 50;
		static const int MONEY_SCORE = 100;

		static const char PLAYER_SYMBOL = '@';

		static const char ENEMY_SYMBOL = 'o';
		static const char MONEY_SYMBOL = '$';

		static const char BRICK_SYMBOL = '#';
		static const char BONUS_BRICK_SYMBOL = '?';
		static const char EMPTY_BRICK_SYMBOL = '-';
		static const char FINISH_SYMBOL = '+';
		
		struct GameState {
			char map[MAP_HEIGHT][MAP_WIDTH + 1];
			jbeau::mario::Mario mario;

			jbeau::brick::Brick *brick = nullptr;
			int brick_length = 0;

			jbeau::enemy::Enemy *enemy = nullptr;
			int enemy_length = 0;
			
			jbeau::money::Money *money = nullptr;
			int money_length = 0;

			int level = 1;
			int score = 0;
			int max_lvl = 3;
		};

		jbeau::brick::Brick *get_new_brick(GameState &state);
		
		jbeau::enemy::Enemy *get_new_enemy(GameState &state);
		void delete_enemy(GameState &state, int i);
		
		jbeau::money::Money *get_new_money(GameState &state);
		void delete_money(GameState &state, int i);
	}
}