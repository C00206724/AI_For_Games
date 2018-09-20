#include "Enemy.h"



Enemy::Enemy() :
	m_velocity(01.0f,01.0f),
	m_position(800,500),
	m_randX(0),
	m_randY(0)
{
	m_knightTexture.loadFromFile("knight.png");
	m_knight.setTexture(m_knightTexture);
	m_knight.setPosition(m_position);
	m_knight.setScale(0.3f, 0.3f);
	
	//random number geneation for velocity and direction
	
	srand(time(0)); // This line is needed to stop the rand() function seeding the same numbers.

	// These while loops just make sure the random number 0 isn't accepted.
	while (m_randX == 0)
	{
		m_randX = rand() % 19 + (-9);
	}

	while (m_randY == 0)
	{
		m_randY = rand() % 19 + (-9);
	}
}


Enemy::~Enemy()
{
}

void Enemy::update(sf::Int32 dt)
{
	m_position.x += (m_velocity.x * m_randX);
	m_position.y += (m_velocity.y * m_randY);
	

	//Window checking
	if (m_position.y > 1850)
	{
		m_position.y = -90;
	}

	if (m_position.y < -200)
	{
		m_position.y = 1840;
	}

	if (m_position.x > 1650)
	{
		m_position.x = -40;
	}

	if (m_position.x < -50)
	{
		m_position.x = 1640;
	}

	m_knight.setPosition(m_position);
}

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(m_knight);
}

float Enemy::getPositionX()
{
	return m_position.x;
}

float Enemy::getPositionY()
{
	return m_position.y;
}