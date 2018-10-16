#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "Enemy.h"

class Game;

class Seek : public Enemy
{
public:
	Seek(Game & game);
	~Seek();
	void update(double dt);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	sf::Vector2f collisionAvoidance(std::vector<Enemy*> enemy);
	int getId();
	float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
	sf::Vector2f normalise();
	float length(sf::Vector2f vel);
	void seek();
	void checkBorders();
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	void KinematicFlee(sf::Vector2f enemyPosition);


private:
	int id = 1;
	float m_maxSpeed;
	float m_radius;
	float m_threshold;
	int m_behaviour;
	float m_orientation;
	float m_velocityF;
	sf::Vector2f m_direction;
	float m_distance;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float m_maxRotation;

	sf::Text m_label;
	sf::Font m_font;

};



