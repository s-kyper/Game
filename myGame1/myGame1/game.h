#pragma once

/////////////////////////////////////
// Include
#include <ctime>
#include <SFML/Graphics.hpp>
#include "gameObject.h"

/////////////////////////////////////
// Constants
const int gameObjectsCountMax = 1024;

/////////////////////////////////////
// Class Game
class Game
{
public:
	Game();
	~Game();

	void setupSystem();
	void initialize();
	bool frame();
	void shutdown();

private:
	void render();
	void update( float dt );

	GameObject* createObject(GameObjectType type, float x, float y, int health);
	void destroyObject( GameObject* object );

private:
	bool m_isGameActive;
	clock_t m_clockLastFrame;

	sf::RenderWindow* m_renderSystem;

	GameObject* m_objects[gameObjectsCountMax];

	float m_shipFireCooldownTime;
	float m_alienAmplitudeTime;
	int score;
	int maxScore;
	clock_t gameTime;
};