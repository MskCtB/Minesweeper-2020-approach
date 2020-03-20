#pragma once
#include <SFML/Graphics.hpp>

class Loader
{
public:
	Loader();
	~Loader();
	const sf::Texture* load(std::string, int val);
	sf::Texture* GetTexture(int val) { return &textures[val]; }
	sf::Font GetFont() { return font; }

private:
	sf::Texture textures[4]; // 0 - nothing, 1 - flag, 2 - bomb, 3 - explosion
	sf::Font font;
};

