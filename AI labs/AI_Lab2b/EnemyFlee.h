#ifndef ENEMYFLEE
#define ENEMYFLEE




#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class EnemyFlee
{
public:
	EnemyFlee();
	~EnemyFlee();
	void update(sf::Int32 dt, sf::Vector2f playerPos);
	void render(sf::RenderWindow & window);
	float getPositionX();
	float getPositionY();
	float getNewRotation(float currentRotation, sf::Vector2f velocity);
	float length(sf::Vector2f velocity);
	void flee(sf::Vector2f playerPos);
	void boundaryCheck();
	sf::Vector2f normalise();

private:
	sf::Sprite m_sprite;
	sf::Texture m_spriteTexture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_heading;
	float m_maxSpeed;
	float m_velocityMag;
	float m_rotation;
	float m_timeToTarget;
	float m_maxRot;
	// random direction and velocity
};

#endif // ENEMYFLEE