#ifndef PLAYER
#define PLAYER
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	void update(sf::Int32 dt);
	void render(sf::RenderWindow & window);
	float getPositionX();
	float getPositionY();

private :
	sf::Sprite m_doggo;
	sf::Texture m_doggoTexture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

};

#endif