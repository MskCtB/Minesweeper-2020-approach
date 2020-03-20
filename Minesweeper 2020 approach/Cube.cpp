#include "Cube.h"


Cube::~Cube()
{
}

void Cube::SetSprite(sf::Texture* texture)
{
	sprite.setTexture(*texture);
}

void Cube::Set(sf::Vector2f pos, sf::Vector2i coordinates)
{
	
	body.setFillColor(sf::Color(192,192,192,255));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(pos);
	sprite.setOrigin(body.getOrigin());
	sprite.setPosition(body.getPosition());
	flag.setOrigin(sprite.getOrigin());
	flag.setPosition(sprite.getPosition());
	position = coordinates;
	number.setFillColor(sf::Color::Blue);
	number.setPosition(body.getPosition().x - number.getCharacterSize() / 4.0f - 2.0f, body.getPosition().y - number.getCharacterSize() / 2.0f - 2.0f);
}

void Cube::Draw(sf::RenderWindow & window)
{
	window.draw(body);
	if (!isCovered)
	{
		if (hasBomb)
			window.draw(sprite);
		else	
			window.draw(number);
	}
	if (isFlagged && isCovered)
		window.draw(flag);
}

void Cube::Update()
{
	std::string string;
	if (bombs > 9 || bombs < 0)
	{
		bombs = 9;
		string = "Error";
	}
	if (hasBomb)
	{
		bombs = 9;
		string = " ";
	}
	if (bombs == 0)
		string = " ";
	else
		string = std::to_string(bombs);
	number.setString(string);
	if (bombs == 1)
		number.setFillColor(sf::Color::Blue);
	if (bombs == 2)
		number.setFillColor(sf::Color(48,255,0));
	if (bombs == 3)
		number.setFillColor(sf::Color::Red);
	if (bombs == 4)
		number.setFillColor(sf::Color(24, 0, 192));
	if (bombs == 5)
		number.setFillColor(sf::Color(192, 0, 24));
	if (bombs == 6)
		number.setFillColor(sf::Color::Cyan);
	if (bombs == 7)
		number.setFillColor(sf::Color::Black);
	if (bombs == 8)
		number.setFillColor(sf::Color(192, 192, 192));

}

void Cube::LeftClick()
{
	if (!isFlagged && isCovered)
	{
		isCovered = false;
		body.setFillColor(sf::Color(128, 128, 128));
	}
	else if (isFlagged && isCovered)
	{ }
	else if (!isCovered)
	{ }
	else
	{ }
}

void Cube::RightClick()
{
	if (isCovered)
		isFlagged = !isFlagged;
}

void Cube::Clean()
{
	bombs = 0;
	isCovered = true;
	isFlagged = false;
	hasBomb = false;
	number.setString("");
	visited = false;
}
