#pragma once

#include "object.hpp"

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
		
		
		extern char map[MAP_HEIGHT][MAP_WIDTH + 1];
		extern jbeau::object::Object mario;

		extern jbeau::object::Object *brick;
		extern int brick_length;

		extern jbeau::object::Object *moving;
		extern int moving_length;

		extern int level;
		extern int score;
		extern int max_lvl;
		
		void delete_moving(int i);
		jbeau::object::Object *get_new_brick();
		jbeau::object::Object *get_new_moving();
		
	}
}