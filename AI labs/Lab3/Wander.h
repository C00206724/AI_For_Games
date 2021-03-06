#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "Enemy.h"

class Game;

class Wander : public Enemy
{
public:
	Wander(Game & game);
	~Wander();
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	sf::Vector2f collisionAvoidance(std::vector<Enemy*> enemy);
	int getId();
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	sf::Vector2f normalise();
	float length(sf::Vector2f vel);
	void wander();
	void checkBorders();
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	void kinematicFlee(sf::Vector2f enemyPosition);

private:
	int id = 5;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	float m_orientation;
	float m_maxRotation;
	sf::Vector2f m_velocity;
	float m_velocityF;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float m_maxSpeed;
	float m_radius;
	float m_threshold;
	int m_behaviour;
	sf::Vector2f m_direction;
	float m_distance;
	float maxRotation = 180;
	float timeToTarget = 2;
	sf::Text m_label;
	sf::Font m_font;
};




