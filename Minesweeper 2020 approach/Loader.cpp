#include "Loader.h"



Loader::Loader()
{
	if (textures[0].loadFromFile("NULL.png"));
	if (textures[1].loadFromFile("Flag.png"));
	if (textures[2].loadFromFile("Bomb.png"));
	if (textures[3].loadFromFile("BOOM.png"));

	if (font.loadFromFile("Arial.ttf"));
}


Loader::~Loader()
{
}

const sf::Texture* Loader::load(std::string, int val)
{
	return &textures[val];
}
