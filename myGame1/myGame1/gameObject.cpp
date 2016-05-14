/////////////////////////////////////
// Include
#include "gameObject.h"
#include "level.h"

/////////////////////////////////////
// Class GameObject
GameObject::GameObject()
{
	m_type = GameObjectType_None;

	m_x = 0.0;
	m_y = 0.0;
	m_xSpeed = 0.0;
	m_ySpeed = 0.0;

	m_symbol = '?';

	m_health = 0;

	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*atlas00);
	setTextureRect(sf::IntRect());
}

GameObject::~GameObject()
{
	if (m_sprite)
		delete m_sprite;
}

void GameObject::render(sf::RenderWindow* rs)
{
	if (m_sprite)
	{
		int row = int(m_y);
		int column = int(m_x);

		m_sprite->setPosition(column * pixelsPerCell, row * pixelsPerCell);

		rs->draw(*m_sprite);
	}
}

void GameObject::update(float dt)
{
	m_y += m_ySpeed * dt;
	m_x += m_xSpeed * dt;
}

bool GameObject::intersects(GameObject* object)
{
	if(int(m_y) == int(object->m_y) && int(m_x) == int(object->m_x))
		return true;

	return false;
}