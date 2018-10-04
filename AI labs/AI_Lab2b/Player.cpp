#include "Player.h"
Player::Player() :
	m_position(100, 100),
	m_velocity(0,0),
	shape(100.0),
	m_rotation(90),
	m_maxSpeed(450),
	m_speed(0),
	m_heading(0,0)

{
	if (!m_texture.loadFromFile("spaceship.png")) {
		//Fail!
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.2, 0.2);
	m_sprite.setOrigin((m_sprite.getTextureRect().width / 2), (m_sprite.getTextureRect().height / 2));
	DEG_TO_RAD = 3.14 / 180;
	
}
Player::~Player()
{

}

void Player::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 20;
	}
}
void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 20;
	}
}
void Player::increaseRotation()
{

	m_rotation += 2.0f;
}
void Player::decreaseRotation()
{
	
	if (m_rotation != 0.00f)
	{
		m_rotation -= 2.0f;
	}
	else
	{
		m_rotation = 359.0f;
	}
	
	
}

void Player::update(double dt)
{
	//key Presses
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		
		speedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speedDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	//setting rotations
	m_heading.x = cos(m_rotation * (3.14 / 180));
	m_heading.y = sin(m_rotation * (3.14 / 180));
	
	m_sprite.setPosition(m_sprite.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_sprite.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_sprite.setRotation(m_rotation + 90);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);

	


}

/// <summary>
/// A function that controls the boundaries for the player
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Player::respawn(float x, float y)
{
	if (y >= 1800 + 100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, -200);
	}

	else if (y < -200)
	{
		m_sprite.setPosition(m_sprite.getPosition().x,1100);
	}
	else if (x < -200)
	{
		m_sprite.setPosition(1700, m_sprite.getPosition().y);
	}
	else if (x >= 1800)
	{
		m_sprite.setPosition(200, m_sprite.getPosition().y);
	}
}

/// <summary>
/// simple render function
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

sf::Vector2f Player::getPos()
{
	//m_sprite.setPosition(m_position);
	std::cout << m_position.x << std::endl;
	std::cout << m_position.y << std::endl;
	return m_position;
}