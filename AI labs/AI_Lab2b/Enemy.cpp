#include "Enemy.h"



Enemy::Enemy() :
	m_velocity(10, 10),
	m_position(800, 500),
	m_maxSpeed(100.0f),
	m_timeToTarget(100.0f)
{
	m_spriteTexture.loadFromFile("knight.png");
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3f, 0.3f);
	//m_velocity.x = 20;
	//m_velocity.y = 20;

	//random number geneation for velocity and direction

	srand(time(0)); // This line is needed to stop the rand() function seeding the same numbers.

					// These while loops just make sure the random number 0 isn't accepted.

}


Enemy::~Enemy()
{
}

void Enemy::update(sf::Int32 dt, sf::Vector2f playerPos)
{
	
	flee(playerPos);


	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
	std::cout << m_position.x << std::endl;
	std::cout << m_position.y << std::endl;
}

float Enemy::getPositionX()
{
	return m_position.x;
}

float Enemy::getPositionY()
{
	return m_position.y;
}

void Enemy::seek(sf::Vector2f playerPos)
{
	m_velocity = playerPos - m_position;
	
	//Magnitude of the vector
	m_velocityMag = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityMag;
	m_velocity.y = m_velocity.y / m_velocityMag;

	m_velocity.x = m_velocity.x * m_velocityMag;
	m_velocity.y = m_velocity.y * m_velocityMag;

	std::cout << m_velocity.x << std::endl;
	m_rotation = getNewRotation(m_rotation, m_velocityMag);
	m_sprite.setPosition(m_position + m_velocity);
	
	


}

/// <summary>
/// Funtion that makes the enemy run away from the player
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
void Enemy::flee(sf::Vector2f playerPos)
{
	m_velocity = playerPos - m_position;
	//divide the velocity so the naked eye can see it
	m_velocity.x = m_velocity.x / m_maxSpeed;
	m_velocity.y = m_velocity.y / m_maxSpeed;
	m_position = m_position - m_velocity;

	
}

float Enemy::getNewRotation(float currentRotation, float speed)
{
	if (speed > 0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentRotation;
	}
}

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Enemy::boundaryCheck()
{
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
}