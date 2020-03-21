#include "Menu.h"
#include "Cube.h"



Menu::Menu(sf::RenderWindow& window) : isActive(true)
{
	sizes[0][0] = 8;	//x1
	sizes[0][1] = 8;	//y1
	sizes[1][0] = 16;	//x2
	sizes[1][1] = 12;	//y2
	sizes[2][0] = 24;	//x3
	sizes[2][1] = 16;	//y3

	button1.setString("8x8");
	button2.setString("12x16");
	button3.setString("16x24");

	font = load.GetFont();
	button1.setFont(font);
	button2.setFont(font);
	button3.setFont(font);

	button1.setFillColor(sf::Color::Black);
	button2.setFillColor(sf::Color::Black);
	button3.setFillColor(sf::Color::Black);

	button1.setCharacterSize(40);
	button2.setCharacterSize(40);
	button3.setCharacterSize(40);
	
	windowSize[0] = sf::Vector2u(sizes[0][0] * (CUBE + 2) + 2, sizes[0][1] * (CUBE + 2) + CUBE + 2);
	windowSize[2] = sf::Vector2u(sizes[2][0] * (CUBE + 2) + 2, sizes[2][1] * (CUBE + 2) + CUBE + 2);

	windowSize[1] = sf::Vector2u(sizes[1][0] * (CUBE + 2) + 2, sizes[1][1] * (CUBE + 2) + CUBE + 2); // 642 x 520
	window.setSize(windowSize[1]); //

	button8x8.setSize(sf::Vector2f(200.0f, 100.0f));
	button8x8.setOrigin(button8x8.getSize() / 2.0f);
	button8x8.setFillColor(sf::Color::Green);
	button8x8.setPosition(200.0f, 180.0f);
	button8x8.setOutlineColor(sf::Color(0, 96, 0));
	button8x8.setOutlineThickness(5);

	button12x16.setSize(sf::Vector2f(200.0f, 100.0f));
	button12x16.setOrigin(button12x16.getSize() / 2.0f);
	button12x16.setFillColor(sf::Color(255, 192, 0));
	button12x16.setPosition(450.0f, 180.0f);
	button12x16.setOutlineColor(sf::Color(192,96,0));
	button12x16.setOutlineThickness(5);

	button16x24.setSize(sf::Vector2f(200.0f, 100.0f));
	button16x24.setOrigin(button16x24.getSize() / 2.0f);
	button16x24.setFillColor(sf::Color::Red);
	button16x24.setPosition(325.0f, 330.0f);
	button16x24.setOutlineColor(sf::Color(96, 0, 0));
	button16x24.setOutlineThickness(5);

	button1.setPosition(button8x8.getPosition().x - 35.0f, button8x8.getPosition().y - 25.0f);
	button2.setPosition(button12x16.getPosition().x - 55.0f, button12x16.getPosition().y - 25.0f);
	button3.setPosition(button16x24.getPosition().x - 55.0f, button16x24.getPosition().y - 25.0f);
}


Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow & window)
{
	window.clear(sf::Color(0,96,255));
	window.setSize(windowSize[1]);
	window.draw(button8x8);
	window.draw(button1);
	window.draw(button12x16);
	window.draw(button2);
	window.draw(button16x24);
	window.draw(button3);
}

int Menu::MouseClick(sf::Vector2i mouse, sf::RenderWindow& window)
{
	if ((mouse.x >= button8x8.getPosition().x - button8x8.getSize().x / 2.0f) && (mouse.x <= button8x8.getPosition().x + button8x8.getSize().x / 2.0f)
		&& (mouse.y >= button8x8.getPosition().y - button8x8.getSize().y / 2.0f) && (mouse.y <= button8x8.getPosition().y + button8x8.getSize().y / 2.0f))
	{
		window.setSize(windowSize[0]);
		isActive = false;
		return 0;
	}
	else if ((mouse.x >= button12x16.getPosition().x - button12x16.getSize().x / 2.0f) && (mouse.x <= button12x16.getPosition().x + button12x16.getSize().x / 2.0f)
		&& (mouse.y >= button12x16.getPosition().y - button12x16.getSize().y / 2.0f) && (mouse.y <= button12x16.getPosition().y + button12x16.getSize().y / 2.0f))
	{
		window.setSize(windowSize[1]);
		isActive = false;
		return 1;
	}
	else if ((mouse.x >= button16x24.getPosition().x - button16x24.getSize().x / 2.0f) && (mouse.x <= button16x24.getPosition().x + button16x24.getSize().x / 2.0f)
		&& (mouse.y >= button16x24.getPosition().y - button16x24.getSize().y / 2.0f) && (mouse.y <= button16x24.getPosition().y + button16x24.getSize().y / 2.0f))
	{
		window.setSize(windowSize[2]);
		isActive = false;
		return 2;
	}
}
