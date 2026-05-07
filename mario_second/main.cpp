#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#define map_width 80
#define map_height 25

typedef struct SObject {
	float x, y;
	float width, height;
	float vert_speed;
	BOOL is_fly;
	char c_type;
	float horiz_speed;
} TObject;

char map[map_height][map_width + 1];
TObject mario;

TObject *brick = NULL;
int brick_length;

TObject *moving = NULL;
int moving_length;

int level = 1;
int score;
int max_lvl;

void clear_map() {
	for (int i = 0; i < map_width; i++) {
		map[0][i] = ' ';
	}
	map[0][map_width] = '\0';
	
	for (int j = 1; j < map_height; j++) {
		sprintf(map[j], map[0]);
	}
}

void show_map() {
	map[map_height - 1][map_width - 1] = '\0';
	for (int j = 0; j < map_height; j++) {
		printf("%s", map[j]);
	}
}

void set_object_pos(TObject *obj, float x_pos, float y_pos) {
	(*obj).x = x_pos;
	(*obj).y = y_pos;
}

void init_object(
	TObject *obj,
	float x_pos, 
	float y_pos, 
	float obj_width, 
	float obj_height, 
	char in_type) {
	set_object_pos(obj, x_pos, y_pos);
	(*obj).width = obj_width;
	(*obj).height = obj_height;
	(*obj).vert_speed = 0;
	(*obj).c_type = in_type;
	(*obj).horiz_speed = 0.5;
}

BOOL is_collision(TObject obj_1, TObject obj_2);
void create_level(int lvl);
TObject *get_new_moving();

void player_dead() {
	system("color 4F");
	Sleep(500);
	create_level(level);
}

void vert_move_object(TObject *obj) {
	(*obj).is_fly = TRUE;
	(*obj).vert_speed += 0.05;
	set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);
	
	for (int i = 0; i < brick_length; i++) {
		if (is_collision(*obj, brick[i])) {
			if (obj[0].vert_speed > 0) {
				obj[0].is_fly = FALSE;
			}
			
			if ((brick[i].c_type == '?') 
				&& (obj[0].vert_speed < 0) 
			    && (obj == &mario)) {
				brick[i].c_type = '-';
				init_object(get_new_moving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
				moving[moving_length - 1].vert_speed = -0.3;
			}
			
			(*obj).y -= (*obj).vert_speed;
			(*obj).vert_speed = 0;

			if (brick[i].c_type == '+') {
				level++;
				
				if (level > max_lvl) {
					level = 1;
				}
				
				system("color 2F");
				Sleep(500);
				create_level(level);
			}
			break;
		}
	}
}

void delete_moving(int i) {
	moving_length--;
	moving[i] = moving[moving_length];
	moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
}

void mario_collision() {
	for (int i = 0; i < moving_length; i++) {
		if (is_collision(mario, moving[i])) {
			if (moving[i].c_type == 'o') {
				if ((mario.is_fly == TRUE) 
					&& (mario.vert_speed > 0) 
					&& (mario.y + mario.height 
					< moving[i].y + moving[i].height * 0.5)) {
					score += 50;
					delete_moving(i);
					i--;
					continue;
				} else {
					player_dead();
				}
			}
			
			if (moving[i].c_type == '$') {
				score += 100;
				delete_moving(i);
				i--;
				continue;
			}
		}
	}
}

void horizon_move_object(TObject *obj) {
	obj[0].x += obj[0].horiz_speed;
	
	for (int i = 0; i < brick_length; i++) { 
		if (is_collision(obj[0], brick[i])) {
			obj[0].x -= obj[0].horiz_speed;
			obj[0].horiz_speed = -obj[0].horiz_speed;
			return;
		}
	}
	
	if (obj[0].c_type == 'o') {
		TObject tmp = *obj;
		vert_move_object(&tmp);
		
		if (tmp.is_fly == TRUE) {
			obj[0].x -= obj[0].horiz_speed;
			obj[0].horiz_speed = -obj[0].horiz_speed;
		}
	}
}

BOOL is_pos_in_map(int x, int y) {
	return ((x >= 0) && (x < map_width) && (y >= 0) && (y < map_height));
}

void put_object_on_map(TObject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int i_width = (int)round(obj.width);
	int i_height = (int)round(obj.height);
	
	for (int i = ix; i < (ix + i_width); i++) {
		for (int j = iy; j < (iy + i_height); j++) {
			if (is_pos_in_map(i, j)) {
				map[j][i] = obj.c_type;
			}
		}
	}
}

void set_cur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void horizon_move_map(float dx) {
	mario.x -= dx;
	for (int i = 0; i < brick_length; i++) {
		if (is_collision(mario, brick[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	
	for (int i = 0; i < brick_length; i++) {
		brick[i].x += dx;
	}
	
	for (int i = 0; i < moving_length; i++) {
		moving[i].x += dx;
	}
}

BOOL is_collision(TObject obj_1, TObject obj_2) {
	return ((obj_1.x + obj_1.width) > obj_2.x) 
		   && (obj_1.x < (obj_2.x + obj_2.width)) 
		   && ((obj_1.y + obj_1.height) > obj_2.y) 
		   && (obj_1.y < (obj_2.y + obj_2.height));
}

TObject *get_new_brick() {
	brick_length++;
	brick = (TObject*)realloc( brick, sizeof(*brick) * brick_length);
	return brick + brick_length - 1;
}

TObject *get_new_moving() {
	moving_length++;
	moving = (TObject*)realloc(moving, sizeof(*moving) * moving_length);
	return moving + moving_length - 1;
}

void put_score_on_map() {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
}

void create_level(int lvl) {
	system("color DF");
	
	brick_length = 0;
	brick = (TObject*)realloc(brick, 0);
	moving_length = 0;
	moving = (TObject*)realloc(moving, 0);
	
	init_object(&mario, 39, 10, 3, 3, '@');
	score = 0;
	
	if (lvl == 1) {
		init_object(get_new_brick(), 20, 20, 40, 5, '#');
		init_object(get_new_brick(), 60, 15, 40, 10, '#');
		init_object(get_new_brick(), 100, 20, 20, 5, '#');
		init_object(get_new_brick(), 120, 15, 10, 10, '#');
		init_object(get_new_brick(), 150, 20, 40, 5, '#');
		init_object(get_new_brick(), 210, 15, 10, 10, '+');
		
		init_object(get_new_brick(), 30, 10, 5, 3, '?');
		init_object(get_new_brick(), 50, 10, 5, 3, '?');
		init_object(get_new_brick(), 60, 5, 10, 3, '-');
		init_object(get_new_brick(), 70, 5, 5, 3, '?');
		init_object(get_new_brick(), 75, 5, 5, 3, '-');
		init_object(get_new_brick(), 80, 5, 5, 3, '?');
		init_object(get_new_brick(), 85, 5, 10, 3, '-');
		
		init_object(get_new_moving(), 25, 10, 3, 2, 'o');
		init_object(get_new_moving(), 80, 10, 3, 2, 'o');
	}
	
	if (lvl == 2) {
		init_object(get_new_brick(), 20, 20, 40, 5, '#');
		init_object(get_new_brick(), 60, 15, 10, 10, '#');
		init_object(get_new_brick(), 80, 20, 20, 5, '#');
		init_object(get_new_brick(), 120, 15, 10, 10, '#');
		init_object(get_new_brick(), 150, 20, 40, 5, '#');
		init_object(get_new_brick(), 210, 15, 10, 10, '+');

		init_object(get_new_moving(), 25, 10, 3, 2, 'o');
		init_object(get_new_moving(), 80, 10, 3, 2, 'o');
		init_object(get_new_moving(), 65, 10, 3, 2, 'o');
		init_object(get_new_moving(), 120, 10, 3, 2, 'o');
		init_object(get_new_moving(), 160, 10, 3, 2, 'o');
		init_object(get_new_moving(), 175, 10, 3, 2, 'o');
	}
	
	if (lvl == 3) {
		init_object(get_new_brick(), 20, 20, 40, 5, '#');
		init_object(get_new_brick(), 80, 20, 15, 5, '#');
		init_object(get_new_brick(), 120, 15, 15, 10, '#');
		init_object(get_new_brick(), 160, 10, 15, 15, '+');

		init_object(get_new_moving(), 25, 10, 3, 2, 'o');
		init_object(get_new_moving(), 50, 10, 3, 2, 'o');
		init_object(get_new_moving(), 80, 10, 3, 2, 'o');
		init_object(get_new_moving(), 90, 10, 3, 2, 'o');
		init_object(get_new_moving(), 120, 10, 3, 2, 'o');
		init_object(get_new_moving(), 130, 10, 3, 2, 'o');
	}
	max_lvl = 3;
}

int main() {
	create_level(level);
	
	do {
		clear_map();
		
		if ((mario.is_fly == FALSE) && (GetKeyState(VK_SPACE) < 0)) {
			mario.vert_speed = -1;
		}
		if (GetKeyState('A') < 0) {
			horizon_move_map(1);
		}
		if (GetKeyState('D') < 0) {
			horizon_move_map(-1);
		}
		
		if (mario.y > map_height) {
			player_dead();
		}
		
		vert_move_object(&mario);
		mario_collision();
		
		for (int i = 0; i < brick_length; i++) {
			put_object_on_map(brick[i]);
		}
		for (int i = 0; i < moving_length; i++) {
			vert_move_object(moving + i);
			horizon_move_object(moving + i);
			if (moving[i].y > map_height) {
				delete_moving(i);
				i--;
				continue;
			}
			put_object_on_map(moving[i]);
		}
		put_object_on_map(mario);
		put_score_on_map();
		
		set_cur(0, 0);
		show_map();
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	return 0;
}