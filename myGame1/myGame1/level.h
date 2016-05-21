#pragma once

/////////////////////////////////////
// Include
#include <SFML/Graphics.hpp>

/////////////////////////////////////
// Extern
extern sf::Texture* atlas00;

/////////////////////////////////////
// Constants
const int screenRows = 25;
const int screenColumns = 50;

const int pixelsPerCell = 15;

const int levelRows = screenRows;
const int levelColumns = screenColumns;

const int levelRandomRows = 10;
const int levelRandomColumns = screenColumns;

const float shipSpeed = 35.0;
const float shipFireCooldown = 0.2;

const float bulletSpeed = 40.0;

const float alienAmplitude = 7.0;
const float alienSpeed = 0.23;

const unsigned char	CellSymbol_Ship		 = 'S';
const unsigned char	CellSymbol_Bullet	 = '|';
const unsigned char	CellSymbol_Alien	 = 'X';

const int shipsMinCoef = 1;
const int shipsMaxCoef = 11;

const unsigned char levelData0[levelRows][levelColumns + 1] =		
{
	"                                                  ",
	"       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       ",
	"       XXXX    XXXX    XXXX    XXXX    XXXX       ",
	"       X   XXXX    XXXX    XXXX    XXXX   X       ",
	"        X   XXXX     XX    XX     XXXX   X        ",
	"         X   XXXXXXXX        XXXXX      X         ",
	"          X XXXX     X X  X X     XXXX X          ",
	"         X  XXXX     XXXXXXXX     XXXX  X         ",
	"            X  X     X      X     X  X            ",
	"             XXX      XXXXXX      XXX             ",
	"              XX      X    X      XX              ",
	"              X         XX         X              ",
	"               X                  X               ",
	"              X                    X              ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                                                  ",
	"                         S                        ",
};

const unsigned char levelRandomData0[levelRandomRows][levelRandomColumns + 1] =
{
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX              ",
	"XXXXXXXX  XXXXXXXXXXXXXXXX  XXXXXXXX              ",
	"XX  XXXX  XX  XXXXXXXX  XX  XXXX  XX              ",
	"XXXX  XXXX                XXXX  XXXX              ",
	"XX  XX  XXXX            XXXX  XX  XX              ",
	"XX  XX    XXXX        XXXX    XX  XX              ",
	"XX  XXXXXX X XXX    XXX X XXXXXX  XX              ",
	"X     XXXX  X   XXXX   X  XXXX     X              ",
	"      XXXXXX    X  X    XXXXXX                    ",
	"X                X  X              X              ",
};

const sf::IntRect alienImage = sf::IntRect(pixelsPerCell, 0, pixelsPerCell, pixelsPerCell);
const sf::IntRect shipImage = sf::IntRect(0, 0, pixelsPerCell, pixelsPerCell);
const sf::IntRect bulletImage = sf::IntRect(0, pixelsPerCell, pixelsPerCell, pixelsPerCell);


/* level for levelColumns = 80
const unsigned char levelData0[levelRows][levelColumns + 1] =
{
	"                                                                                ",
	"                                                                                ",
	"       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       ",
	"         X  XXXX XX XXXXXXX  XXXXXXXXXXXXXXXXXXXXXX  XXXXXXX XX XXXX  X         ",
	"       XXXXXXXXX    X  X  X  X  XXX  XXXXXX  XXX  X  X  X  X    XXXXXXXXX       ",
	"            XXXX    X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X    XXXX            ",
	"            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
	"            X  X                  XXXXXXXXXXXX                  X  X            ",
	"                                  XX  XXXX  XX                                  ",
	"                                  XX  X  X  XX                                  ",
	"                                  X          X                                  ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                       S                                        ",
};

const unsigned char levelRandomData0[levelRandomRows][levelRandomColumns + 1] =
{
	"                                                                                ",
	"              XXXX    XXXX    XXXX    XXXX    XXXX    XXXX    XXXX              ",
	"              X  XXXXX   XXXXXX  XXXXXX  XXXXXX  XXXXXX  XXXXXX  X              ",
	"              XXXXXXXXX    X  X  X  X X  X X  X  X  X    XXXXXXXXX              ",
	"              XXXX    X  X  X  XXXXX        XXXXX  X  X  X    XXXX              ",
	"              XXXX            X   XXXXXXXXXXXX   X            XXXX              ",
	"              X  X                 XXXXXXXXXX                 X  X              ",
	"                                  XX  XXXX  XX                                  ",
	"                                  XX  X  X  XX                                  ",
	"                                  X          X                                  ",
};*/