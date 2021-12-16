#pragma once
#include "ConsoleUtils.h"
#include "Map.h"

#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */

class Enemy
{
private:
	COORD spawn;
	COORD position;
	COORD direction;

	char character = 'X';

	ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::BLACK;

	void RandomDirection();

public:
	enum ENEMY_STATE { ENEMY_NONE, ENEMY_KILLED, ENEMY_DEAD };
	Enemy();
	Enemy(COORD _spawn);

	void Draw();
	ENEMY_STATE Update(Map* _map, COORD _player);
};