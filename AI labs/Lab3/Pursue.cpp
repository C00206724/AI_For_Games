#include "Pursue.h"

Pursue::Pursue(Game & game) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_relVelocity(0, 0),
	shape(100.0f),
	m_maxSpeed(3.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(80.0f),
	m_maxTimePrediction(3.0f),
	m_relSpeed(0.0f),
	m_radius(10.0f),
	m_threshold(35),
	m_behaviour(1)
{

	if (!m_texture.loadFromFile("EnemyRocket.png")) {
		//do something
	}
	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(200, 150));
	m_position = sf::Vector2f(0, 0);
	m_rect.setPosition(m_position);

	initFont();

}
void Pursue::initFont()
{
	m_label.setFont(m_font);
	m_label.setCharacterSize(40);
	m_label.setString("Pursue");
	m_label.setPosition(m_position.x, m_position.y);
	m_label.setOrigin(50, 50);
	m_label.setFillColor(sf::Color(0, 0, 0));
}

Pursue::~Pursue()
{

}
sf::Vector2f Pursue::getPosition()
{
	return m_rect.getPosition();
}
sf::Vector2f Pursue::getVelocity()
{
	return m_velocity;
}
int Pursue::getId()
{
	return id;
}
float Pursue::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
void Pursue::respawn(float x, float y)
{


	if (x > 2020)
	{
		m_position.x = -200;
		m_velocity.x = getRandom(10, 1);
		m_velocity.y = getRandom(21, -10);
	}
	if (x < -200)
	{
		m_position.x = 1920;
		m_velocity.x = getRandom(-10, -1);
		m_velocity.y = getRandom(21, -10);
	}
	if (y < -200)
	{
		m_position.y = 1080;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(-10, -1);
	}
	if (y > 1180)
	{
		m_position.y = -200;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(10, 1);
	}

}

float Pursue::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}


sf::Vector2f Pursue::collisionAvoidance(std::vector<Enemy*> enemies) {


	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getId() != id)
		{
			//Vector player to enemy
			m_direction = enemies[i]->getPosition() - m_position;
			m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);

			if (m_distance <= m_radius)
			{
				float dot = (m_velocity.x * m_direction.x) + (m_velocity.y * m_direction.y);
				float det = (m_velocity.x * m_direction.y) - (m_velocity.y * m_direction.x);

				float angle = atan2(det, dot);
				if (angle >= -m_threshold && angle <= m_threshold)
				{
					m_behaviour = 2;
					KinematicFlee(enemies[i]->getPosition());
					std::cout << "Collided Pursue" << std::endl;

				}

			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
			}



		}
	}
	return m_velocity;
}

void Pursue::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}
void Pursue::KinematicFlee(sf::Vector2f enemyPosition)
{
	m_velocity = m_position - enemyPosition;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}
void Pursue::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;

			m_velocity = m_velocity * m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}

}
void Pursue::pursue(sf::Vector2f playerPosition, sf::Vector2f playerVelocity)
{

	m_direction = playerPosition - m_position;


	m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);


	m_speed = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	if (m_speed <= m_distance / m_maxTimePrediction) {

		m_timePrediction = m_maxTimePrediction;
	}
	else {
		m_timePrediction = m_distance / m_speed;
	}

	m_targetPos = playerPosition + playerVelocity * m_timePrediction;


	kinematicArrive(m_targetPos);

}
void Pursue::update(double dt)
{

	pursue(m_game->getPlayerPos(), m_game->getPlayerVel());
	m_position = m_position + m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_orientation);
	respawn(m_rect.getPosition().x, m_rect.getPosition().y);

	//resetting label postions
	m_label.setPosition(m_position);
	m_label.setRotation(m_orientation);
}


void Pursue::render(sf::RenderWindow & window)
{

	window.draw(m_rect);
	window.draw(m_label);
}