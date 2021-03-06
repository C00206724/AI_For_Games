#include "EnemyFlee.h"

EnemyFlee::EnemyFlee() :
	m_velocity(10, 10),
	m_position(600, 500),
	m_maxSpeed(2.0f),
	m_timeToTarget(100.0f),
	m_maxRot(20)
{
	m_spriteTexture.loadFromFile("asteroid.png");
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3f, 0.3f);
	//m_velocity.x = 20;
	//m_velocity.y = 20;

	//random number geneation for velocity and direction

	srand(time(0)); // This line is needed to stop the rand() function seeding the same numbers.

}


EnemyFlee::~EnemyFlee()
{
}

void EnemyFlee::update(sf::Int32 dt, sf::Vector2f playerPos)
{

	flee(playerPos);



	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
}

float EnemyFlee::getPositionX()
{
	return m_position.x;
}

float EnemyFlee::getPositionY()
{
	return m_position.y;
}



sf::Vector2f EnemyFlee::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}
/// <summary>
/// Funtion that makes the enemy run away from the player
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
void EnemyFlee::flee(sf::Vector2f playerPos)
{
	m_velocity = playerPos - m_position;
	m_velocity = normalise();
	m_velocity = m_velocity * m_maxSpeed;
	m_rotation = getNewRotation(m_rotation, m_velocity);
	m_position = m_position - m_velocity;

}



float EnemyFlee::getNewRotation(float currentRotation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentRotation;
	}
}

/// <summary>
/// A useful function to have in the long term
/// Code usually makes things look complicated
/// </summary>
/// <param name="velocity"></param>
/// <returns></returns>
float EnemyFlee::length(sf::Vector2f velocity) {
	return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

void EnemyFlee::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void EnemyFlee::boundaryCheck()
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
