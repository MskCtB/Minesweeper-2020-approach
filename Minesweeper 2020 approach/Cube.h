#pragma once
#include "Loader.h"
#include <string>
#include <iostream>

constexpr float CUBE = 38.0f;

class Cube
{
public:
	Cube() : body(sf::Vector2f(CUBE, CUBE)), hasBomb(false), isFlagged(false), isCovered(true) , bombs(0), visited(false)
			{ number.setCharacterSize(24); number.setPosition(body.getPosition()); };
	~Cube();
	void SetFont(sf::Font font) { this->font = font; number.setFont(this->font); }
	void SetSprite(sf::Texture* texture);
	void SetFlagSprite(sf::Texture* texture) { flag.setTexture(*texture); }
	void Set(sf::Vector2f pos, sf::Vector2i coordinates);
	void Draw(sf::RenderWindow & window);
	void SetBomb() { hasBomb = true; }
	bool Status() { return hasBomb; }
	void Update();
	void LeftClick();
	void RightClick();
	bool CheckFlag() { return isFlagged; }
	bool CheckCover() { return isCovered; }
	void Reveal() { isCovered = false; body.setFillColor(sf::Color(128, 128, 128)); }


	void Clean();
	
	bool visited;
	int bombs;
private:
	sf::Font font;
	sf::RectangleShape body;
	sf::Sprite sprite;
	sf::Sprite flag;
	sf::Text number;
	sf::Vector2i position;
	bool hasBomb;
	bool isFlagged;
	bool isCovered;
};

