#pragma once
#include "Loader.h"

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();
	void Draw(sf::RenderWindow& window);
	void TurnOn() { isActive = true; }
	bool MenuState() { return isActive; }
	int MouseClick(sf::Vector2i mouse, sf::RenderWindow& window);
	const sf::Vector2u* GetSizes() { return windowSize; }

private:
	Loader load;
	sf::RectangleShape button8x8, button12x16, button16x24;
	sf::Text button1, button2, button3;
	sf::Font font;
	int sizes[3][2];
	sf::Vector2u windowSize[3];
	bool isActive;
};

