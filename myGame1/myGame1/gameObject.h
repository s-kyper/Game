#pragma once

/////////////////////////////////////
// Include
#include <SFML/Graphics.hpp>

/////////////////////////////////////
// Enum
enum GameObjectType
{
	GameObjectType_None,
	GameObjectType_Ship,
	GameObjectType_Bullet,
	GameObjectType_Alien
};


/////////////////////////////////////
// Class GameObject
class GameObject
{
public:
	GameObject();
	~GameObject();

	void render(sf::RenderWindow* rs);
	void update(float dt);

	bool intersects(GameObject* object);


	void setType(GameObjectType type) { m_type = type; }
	GameObjectType getType() { return m_type; }

	void setX(float x) { m_x = x; }
	float getX() { return m_x; }

	void setY(float y) { m_y = y; }
	float getY() { return m_y; }

	void setXSpeed(float xSpeed) { m_xSpeed = xSpeed; }
	float getXSpeed() { return m_xSpeed; }

	void setYSpeed(float ySpeed) { m_ySpeed = ySpeed; }
	float getYSpeed() { return m_ySpeed; }

	void setSymbol(char symbol) { m_symbol = symbol; }
	char getSymbol() { return m_symbol; }

	void decreaseHealth() { m_health--; }
	void setHealth(int health) { m_health = health; }
	int getHealth() { return m_health; }

	sf::Sprite* m_sprite;

	void setSpriteColor(sf::Color color) { m_sprite->setColor(color); }
	void setTextureRect(sf::IntRect rect) { m_sprite->setTextureRect(rect); }

private:
	GameObjectType m_type;

	float m_x;
	float m_y;
	float m_xSpeed;
	float m_ySpeed;

	char m_symbol;

	int m_health;
};