#pragma once
#include "Cube.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

class Game
{
public:
	Game();
	~Game();
	void Set_Up();
	void Draw(sf::RenderWindow& window);
	void Clean();
	void RightClick(sf::Vector2i mouse);
	void LeftClick(sf::Vector2i mouse);
	void SetBombs();
	void Uncover(int y, int x);
	void GameOver();
	inline void SetAmount(int i) { amount = i; }
	void UpdateString() { string = std::to_string(amount); BombCounter.setString("Bombs: " + string); }
	void DrawGameOver(sf::RenderWindow& window);
	void Colour();
	void Win();

	bool alive;

private:
	//sf::Clock clock;
	sf::Vector2i positions[8][8];
	int amount;
	int AtoS;
	std::string string;
	Loader loader;
	Cube arr[8][8];
	sf::Text BombCounter;
	sf::Font font;
	sf::Text GO;
	sf::Text GO2;
	int colour, flash;
	bool win;
};

