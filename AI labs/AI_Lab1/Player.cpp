#include "Player.h"



Player::Player() :
	m_velocity(10, 10),
	m_position(500,500)
{
	if (!m_doggoTexture.loadFromFile("dog.png"))
	{
		std::cout << "Dog not loaded" << std::endl;
	}
	m_doggo.setTexture(m_doggoTexture);
	m_doggo.setPosition(m_position);
	m_doggo.setScale(0.2, 0.2);



}


Player::~Player()
{
}


void Player::update(sf::Int32 dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) == true)
	{
		m_position.y -= m_velocity.y;
		m_doggo.setPosition(m_position);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) == true)
	{
		m_position.y += m_velocity.y;
		m_doggo.setPosition(m_position);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == true)
	{
		m_position.x += m_velocity.x;
		m_doggo.setPosition(m_position);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == true)
	{
		m_position.x -= m_velocity.x;
		
	}

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

	m_doggo.setPosition(m_position);
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_doggo);

}

float Player::getPositionX()
{
	return m_position.x;
}

float Player::getPositionY()
{
	return m_position.y;
}