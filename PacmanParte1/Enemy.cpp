#include "Enemy.h"

void Enemy::RandomDirection()
{
	direction = { 0,0 };

	int random = rand() % 4; /* Random number between 0 - 3*/

	switch (random) {
	case 0:
		direction.X = 1;
		break;
	case 1:
		direction.X = -1;
		break;
	case 2:
		direction.Y = 1;
		break;
	case 3:
		direction.Y = -1;
		break;
	}
}

Enemy::Enemy()
{
	spawn = { 0,0 };
	position = spawn;
	direction = { 0,0 };
}

Enemy::Enemy(COORD _spawn)
{
	position = _spawn;
	spawn = _spawn;
	direction = { 0,0 };
}

void Enemy::Draw()
{
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);

	std::cout << character;
}

void Enemy::PowerUpPicked()
{
	PowerUpCountDown = TimeManager::getInstance().time + PowerUpCountDown_Time;
}

Enemy::ENEMY_STATE  Enemy::Update(Map* _map, COORD _player)
{
	
	RandomDirection();

	COORD newPosition = position; /*Creating new position vars to check collisions*/
	newPosition.X += direction.X;
	newPosition.Y += direction.Y;


	if (newPosition.X < 0) /* Teleporting enemy when reach end of map */
	{
		newPosition.X = _map->Width - 1;
	}
	newPosition.X %= _map->Width;
	if (newPosition.Y < 0)
	{
		newPosition.Y = _map->Height - 1;
	}
	newPosition.Y %= _map->Height;


	switch (_map->GetTile(newPosition.X, newPosition.Y)) /* Checking collisions */
	{
	case Map::MAP_TILES::MAP_WALL: /* If enemy collides with wall, undo the move */
		newPosition = position;
		break;
	}

	position = newPosition; /* Moving the enemy */

	ENEMY_STATE state = ENEMY_STATE::ENEMY_NONE;
	if (position.X == _player.X && position.Y == _player.Y)
	{
		if (PowerUpCountDown <= TimeManager::getInstance().time)
		{
			state = ENEMY_STATE::ENEMY_DEAD;
		}
		else
		{
			position = spawn;
			state = ENEMY_STATE::ENEMY_KILLED;
		}
		
	}
	if (PowerUpCountDown <= TimeManager::getInstance().time)
	{
		foreground = foreground_attack;
	}
	else
	{
		foreground = foreground_powerUp;
	}
	return state;
}