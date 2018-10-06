#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "EnemySeek.h"
#include "EnemyFlee.h"
#include "EnemyWander.h"

class Game
{
public:
	Game();
	void run();

private:
	void update(sf::Int32 dt);
	void render();


	sf::RenderWindow m_window;

	//Player
	Player *m_player;

	//Enemy
	EnemyFlee *m_enemyFlee;
	EnemyWander *m_enemyWander;
	EnemySeek *m_enemySeek;


	//speed
	sf::Vector2f m_velocity;
};
#endif // !GAME_H


