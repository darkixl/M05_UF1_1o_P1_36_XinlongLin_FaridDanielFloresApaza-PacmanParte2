#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "TimeManager.h"

#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */

class Enemy
{
private:
	COORD spawn;
	COORD position;
	COORD direction;

	char character = 'X';
	float PowerUpCountDown = 0;
	const float PowerUpCountDown_Time = 15;
	ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::BLACK;

	ConsoleUtils::CONSOLE_COLOR foreground_attack = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR foreground_powerUp = ConsoleUtils::CONSOLE_COLOR::DARK_CYAN;
	void RandomDirection();

public:
	enum ENEMY_STATE { ENEMY_NONE, ENEMY_KILLED, ENEMY_DEAD };
	Enemy();
	Enemy(COORD _spawn);

	void Draw();
	void PowerUpPicked();
	ENEMY_STATE Update(Map* _map, COORD _player);
};