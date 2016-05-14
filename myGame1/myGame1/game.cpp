/////////////////////////////////////
// Include
#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "level.h"
#include "input.h"
#include <Windows.h>
#include <sstream>

sf::Texture* atlas00 = 0;
sf::Font* font;
sf::Text* text;

boolean brokenHighscore;

/////////////////////////////////////
// Class Game
Game::Game()
{
	m_isGameActive = true;
	m_clockLastFrame = 0;
	score = 0;

	for (int i = 0; i < gameObjectsCountMax; i++)
		m_objects[i] = 0;

	m_shipFireCooldownTime = 0.0;
	m_alienAmplitudeTime = 0.0;

	m_renderSystem = 0;

	brokenHighscore = false;
}

Game::~Game() {
	if (atlas00)
		delete atlas00;

	if (m_renderSystem)
		delete m_renderSystem;
}

void Game::setupSystem()
{
	srand(time(0));

	m_renderSystem = new sf::RenderWindow(
		sf::VideoMode(pixelsPerCell * screenColumns + 7 * pixelsPerCell, pixelsPerCell * screenRows, 32), 
		"Space invaders",
		sf::Style::Titlebar | sf::Style::Close);

	atlas00 = new sf::Texture();
	atlas00->loadFromFile("atlas00.png");
	font = new sf::Font();
	font->loadFromFile("ARIAL.TTF");
	text = new sf::Text();
	text->setFont(*font);
	text->setCharacterSize(15);
	text->setColor(sf::Color::Yellow);
	text->setStyle(sf::Text::Bold);
	text->setPosition(0, 0);

	freopen("statistics.txt", "r", stdin);
	std::cin >> maxScore;
	fclose(stdin);
}

void Game::initialize()
{
	m_shipFireCooldownTime = 0.0;
	m_alienAmplitudeTime = 0.0;
	score = 0;

	// Load level
	for (int r = 0; r < levelRows; r++)
	{
		for (int c = 0; c < levelColumns; c++)
		{
			unsigned char cellSymbol = levelData0[r][c];

			switch(cellSymbol)
			{
				// Create Ship
				case CellSymbol_Ship:
				{
					GameObject* ship = createObject(GameObjectType_Ship, (c + 0.5), r, 1);
					ship->setTextureRect(shipImage);
					break;
				}

				// Create Alien
				case CellSymbol_Alien:
				{
					GameObject* alien = createObject(GameObjectType_Alien, (c + 0.5), r, 1); 
					alien->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
					alien->setYSpeed(alienSpeed);
					alien->setTextureRect(alienImage);
					break;
				}
			}
		}
	}
}

bool Game::frame()
{
	if (!m_renderSystem->isOpen())
		return false;

	// Calculate delta time
	clock_t clockNow = clock();
	gameTime = clockNow % cooldownTime;
	clock_t deltaClock = clockNow - m_clockLastFrame;
	float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
	m_clockLastFrame = clockNow;

	sf::Event event;
	while (m_renderSystem->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_renderSystem->close();
	}

	render();
	update(deltaTime);

	return m_isGameActive;
}

void Game::shutdown()
{
	for (int i = 0; i < gameObjectsCountMax; i++)
		if(m_objects[i] != 0)
		{
			delete m_objects[i];
			m_objects[i] = 0;
		}

	if (score > maxScore) {
		freopen("statistics.txt", "w", stdout);
		std::cout << score;
		fclose(stdout);
	}
}

void Game::render()
{
	// Start frame
	m_renderSystem->clear(sf::Color(0, 0, 0));  // black background

	// Draw all game objects
	int objectsCount = 0;
	for (int i = 0; i < gameObjectsCountMax; i++) 
		if (m_objects[i] != 0)
		{
			 m_objects[i]->render(m_renderSystem);
			 objectsCount++;
		}

	std::ostringstream osscore;
	osscore << score;
	if ((score <= maxScore) || ((brokenHighscore) && (score - maxScore >= 10))) {
		text->setString("score: " + osscore.str());
	}
	else {
		text->setString("score: " + osscore.str() + ". Congratulations! You broke a highscore!");
		brokenHighscore = true;
	}
	m_renderSystem->draw(*text);
	m_renderSystem->display();
}

void Game::update(float dt)
{
	// Update all game objects
	for (int i = 0; i < gameObjectsCountMax; i++) 
	{
		GameObject* object = m_objects[i];

		if(object != 0)
		{
			 object->update(dt);

			 switch(object->getType())
			 {
				 // Hero ship
				 case GameObjectType_Ship:
				 {
					 // Borders
					 if(object->getX() < 0)
						 object->setX(0);
					 else
					 if(object->getX() > screenColumns - 1)
						 object->setX(screenColumns - 1);

					// Move
					if(IsKeyDown(VK_LEFT))
						object->setXSpeed(-shipSpeed);
					else
					if(IsKeyDown(VK_RIGHT))
						object->setXSpeed(shipSpeed);
					else
						object->setXSpeed(0.0);
	 
					// Fire
					if(IsKeyDown(VK_SPACE))
					{
						if(m_shipFireCooldownTime <= 0.0)
						{
							m_shipFireCooldownTime = shipFireCooldown;

							// Create bullet
							{
								GameObject* bullet = createObject(GameObjectType_Bullet, object->getX(), object->getY() - 1, 1);
								bullet->setYSpeed(-bulletSpeed);
								bullet->setTextureRect(bulletImage);
							}
						}
					}
				 }

				 // Bullet
				 case GameObjectType_Bullet:
				 {
					 if(object->getY() < 0)
					 {
						destroyObject(object);
					 }
					 else
					 {
						for(int e = 0; e < gameObjectsCountMax; e++) 
						{
							GameObject* anotherObject = m_objects[e];

							if(anotherObject != 0)
							{
								if(anotherObject->getType() == GameObjectType_Alien)
								{
									if (anotherObject->intersects(object))
									{
										score++;
										anotherObject->decreaseHealth();
										if (anotherObject->getHealth() == 0) {
											destroyObject(anotherObject);
										}
										else {
											int k = anotherObject->getHealth();
											anotherObject->setTextureRect(sf::IntRect(k * pixelsPerCell, 0, pixelsPerCell, pixelsPerCell));
										}
										destroyObject(object);
									}
								}
							}
						}
					 }
					 break;
				 }

				 // Alien ship
				 case GameObjectType_Alien:
				 {
					 if (object->getY() >= screenRows - 1)
						 m_isGameActive = false;
					 else
						 object->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
					 break;
				 }
			 }
		}
	}
	

	if ((gameTime % cooldownTime == 0)) {
		float k = score / 50;
		if (k < shipsMinCoef) k = shipsMinCoef;
		if (k >= shipsMaxCoef) k = shipsMaxCoef;
		int r = GetRandomInt(0, levelRandomRows - 1);
		for (int c = 0; c < levelColumns; c++)
		{
			unsigned char cellSymbol = levelRandomData0[r][c];
			int alienHealth = GetRandomInt(1, k);
			switch (cellSymbol)
			{
				// Create Alien
				case CellSymbol_Alien:
				{
					GameObject* alien = createObject(GameObjectType_Alien, (c  + 0.5), 1, alienHealth);
					alien->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
					alien->setYSpeed(alienSpeed);
					alien->setTextureRect(sf::IntRect(alienHealth * pixelsPerCell, 0, pixelsPerCell, pixelsPerCell));
					break;
				}
			}
		}
	}

	// Ship cooldown time
	if(m_shipFireCooldownTime > 0.0)
		m_shipFireCooldownTime -= dt;

	// Alien amplitude time
	m_alienAmplitudeTime += dt;
}

GameObject* Game::createObject(GameObjectType type, float x, float y, int health)
{
	// Find free pointer and create object
	for(int i = 0; i < gameObjectsCountMax; i++)
	{	
		if(m_objects[i] == 0)
		{
			GameObject* object = new GameObject();

			object->setType(type);
			object->setX(x);
			object->setY(y);
			object->setHealth(health);

			m_objects[i] = object;
			return object;
		}
	}

	return 0;
}

void Game::destroyObject(GameObject* object)
{
	for(int i = 0; i < gameObjectsCountMax; i++)
	{	
		if(m_objects[i] == object)
		{
			delete m_objects[i];
			m_objects[i] = 0;
			return;
		}
	}
}