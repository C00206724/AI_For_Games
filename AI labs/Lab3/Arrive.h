#pragma once
#ifndef ARRIVE
#define ARRIVE
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "Enemy.h"

class Game;

class Arrive : public Enemy
{
public:
	Arrive(Game & game);
	~Arrive();
	void update(double dt);
	void render(sf::RenderWindow & window);
	float getNewOrientation(float currentOrientation, float velocity);
	sf::Vector2f normalise(sf::Vector2f vec);
	sf::Vector2f collisionAvoidance(std::vector<Enemy*> enemies);
	float length(sf::Vector2f vel);
	void arrive();
	void checkBorders();
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	void initFont();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	int getId();
	void KinematicFlee(sf::Vector2f enemyPosition);


private:
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	float m_velocityF;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float m_maxSpeed;
	float m_threshold;
	int m_behaviour;
	sf::Vector2f m_direction;
	float m_distance;
	float maxRotation = 0;
	float timeToTarget = 10;
	float m_orientation;
	sf::Text m_label;
	sf::Font m_font;


	int id = 2;
	float distance;
	sf::Vector2f m_relVelocity;
	sf::Vector2f m_relPosition;
	sf::Vector2f m_steering;
	float m_relSpeed;
	float m_timeToCollision;
	float m_minSeperation;
	float m_shortestTime;
	float m_radius;
};

#endif