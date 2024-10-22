#include "bat.hpp"

// Constructor
bat::bat(float startX, float startY) : m_Position(startX, startY)
{
	m_Shape.setSize(sf::Vector2f(50,5));
	m_Shape.setPosition(m_Position);
}

FloatRect bat::getPosition()
{
	return m_Shape.getGlobalBounds();
}

RectangleShape bat::getShape()
{
	return m_Shape;
}

void bat::moveLeft()
{
	m_MovingLeft = true;
}


void bat::moveRight()
{
	m_MovingRight = true;
}


void bat::stopLeft()
{
	m_MovingLeft = false;
}


void bat::stopRight()
{
	m_MovingRight = false;
}

void bat::update(Time dt)
{
	if (m_MovingLeft)
	{
		m_Position.x -= m_Speed * dt.asSeconds();
	}
	
	if (m_MovingRight)
	{
		m_Position.x += m_Speed * dt.asSeconds();
	}
	
	m_Shape.setPosition(m_Position);
}













