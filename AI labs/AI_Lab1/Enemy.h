#ifndef ENEMY
#define ENEMY


#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void update(sf::Int32 dt);
	void render(sf::RenderWindow & window);
	float getPositionX();
	float getPositionY();

private :
	sf::Sprite m_knight;
	sf::Texture m_knightTexture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	int m_randX;
	int m_randY;
};

#endif // !ENEMY