#include "Wander.h"

double const Wander::DEG_TO_RAD = 3.14 / 180.0f;
double const Wander::RAD_TO_DEG = 180.0f / 3.14;
Wander::Wander(Game &game) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_maxSpeed(2.0f),
	m_maxRotation(20.0f),
	m_radius(250.0f),
	m_threshold(30.0f),
	m_behaviour(1)


{
	if (!m_texture.loadFromFile("Enemyrocket.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(m_position.x + 100, m_position.y + 50);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_rect.setPosition(m_position);
	srand(time(NULL));

}


Wander::~Wander()
{
}



void Wander::wander()
{
	m_velocity = m_game->getPlayerPos() - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//m_velocityF = m_velocityF * m_maxSpeed;
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;


	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	m_orientation = m_orientation + m_maxRotation * getRandom(2, -1);
	m_velocity.x = (-sin(m_orientation)) * m_maxSpeed;
	m_velocity.y = cos(m_orientation) * m_maxSpeed;
}

float Wander::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Wander::checkBorders()
{
	if (m_rect.getPosition().x > 2020)
	{
		m_position.x = -200;
	}
	if (m_rect.getPosition().x < -200)
	{
		m_position.x = 1920;
	}
	if (m_rect.getPosition().y < -200)
	{
		m_position.y = 1080;
	}
	if (m_rect.getPosition().y > 1180)
	{
		m_position.y = -200;
	}
}
void Wander::update(double dt)
{
	checkBorders();
	wander();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_orientation);

}


float Wander::getNewOrientation(float curOrientation, float velocity)
{
	if (velocity > 0)
	{
		float rotation = atan2(-m_velocity.x, m_velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}

sf::Vector2f Wander::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Wander::getVelocity()
{
	return m_velocity;
}

int Wander::getId()
{
	return id;
}

void Wander::kinematicFlee(sf::Vector2f enemyPosition)
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

sf::Vector2f Wander::collisionAvoidance(std::vector<Enemy*> enemies) {


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
					kinematicFlee(enemies[i]->getPosition());
					//std::cout << "Collided Wander" << std::endl;

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

void Wander::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::Vector2f Wander::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}
// Returns the length of the vector
float Wander::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}