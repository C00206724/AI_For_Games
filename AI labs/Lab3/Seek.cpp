#include "Seek.h"

double const Seek::DEG_TO_RAD = 3.14 / 180.0f;
double const Seek::RAD_TO_DEG = 180.0f / 3.14;

Seek::Seek(Game &game) :
	m_game(&game),
	m_position(300, 500),
	m_velocity(0, 0),
	m_maxSpeed(1.5f),
	m_maxRotation(20.0f),
	m_behaviour(1),
	m_radius(250.0f),
	m_threshold(30.0f)
{
	if (!m_texture.loadFromFile("EnemyRocket.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_rect.setPosition(m_position);
	srand(time(NULL));

}


Seek::~Seek()
{
}

void Seek::checkBorders()
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
void Seek::update(double dt)
{
	checkBorders();
	seek();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);



}


void Seek::seek()
{
	m_velocity = m_game->getPlayerPos() - m_position;
	m_velocity = normalise();
	m_velocity = m_velocity * m_maxSpeed;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
}

float Seek::getNewOrientation(float curOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-m_velocity.x, m_velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}

sf::Vector2f Seek::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Seek::getVelocity()
{
	return m_velocity;
}

int Seek::getId()
{
	return id;
}

void Seek::KinematicFlee(sf::Vector2f enemyPosition)
{
	m_velocity = m_position - enemyPosition;

	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);


	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;


	m_orientation = getNewOrientation(m_orientation, m_velocity);

}

sf::Vector2f Seek::collisionAvoidance(std::vector<Enemy*> enemies) {


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
					//std::cout << "Collided Seek" << std::endl;

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

void Seek::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::Vector2f Seek::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}

// Returns the length of the vector
float Seek::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}
